#include "graph-flow/contour-correction/model/graph/GraphModel.h"

namespace GraphFlow::ContourCorrection::Graph {

Domain getReducedDomain(const GraphSegInput& gfi,
                        const DigitalSet& candidateDS) {
  using namespace DGtal::Z2i;

  Point lb, ub;
  candidateDS.computeBoundingBox(lb, ub);
  Point optBandBorder(gfi.optBand + 1, gfi.optBand + 1);

  return Domain(lb - 2 * optBandBorder, ub + 2 * optBandBorder);
}

void buildLevelSet(DigitalSet& levelSet, const GraphSegInput& gfi,
                   const DigitalSet& candidateDS, DTL2& dtInterior,
                   DTL2& dtExterior) {
  using namespace DGtal::Z2i;

  const Domain& domain = candidateDS.domain();

  DigitalSet _levelSet =
      GraphFlow::Utils::Digital::Misc::level(dtInterior, gfi.optBand, 0);
  _levelSet +=
      GraphFlow::Utils::Digital::Misc::level(dtExterior, gfi.optBand, 0);

  for (auto p : _levelSet)
    if (domain.isInside(p)) levelSet.insert(p);
}

DigitalSet* optimizeConnectedComponent(DigitalSet& vertexSet,
                                       const GraphSegInput& gfi,
                                       const DigitalSet& candidateDS) {
  using namespace DGtal::Z2i;

  const Domain& domain = candidateDS.domain();
  Domain reducedDomain = getReducedDomain(gfi, candidateDS);

  auto dtInterior = GraphFlow::Utils::Digital::Misc::interiorDistanceTransform(
      reducedDomain, candidateDS);
  auto dtExterior = GraphFlow::Utils::Digital::Misc::exteriorDistanceTransform(
      reducedDomain, candidateDS);

  buildLevelSet(vertexSet, gfi, candidateDS, dtInterior, dtExterior);

  auto ewv = prepareEdgeWeightVector(gfi, candidateDS,
                                     gfi.dataDistribution.segResultImg);

  auto twv = prepareTerminalWeights(gfi, candidateDS, dtInterior, dtExterior);

  FlowGraph fg(vertexSet, twv, ewv);
  DigitalSet* solutionSet = new DigitalSet(domain);
  GraphFlow::Utils::Digital::SetOperations::setDifference(
      *solutionSet, candidateDS, vertexSet);
  solutionSet->insert(fg.sourceNodes.begin(), fg.sourceNodes.end());

  for (auto ew : ewv) delete ew;
  for (auto tw : twv) delete tw;

  return solutionSet;
}

double regionValue(double& fgv, double& bgv, const DigitalSet& ds,
                   const Image::CVMatDistribution& fgDistr,
                   const Image::CVMatDistribution& bgDistr) {
  const cv::Mat& img = fgDistr.img;
  bgv = 0;
  fgv = 0;
  for (auto p : ds.domain()) {
    int prow = img.rows - p[1] - 1;
    int pcol = p[0];

    if (ds(p)) {
      fgv += -log((fgDistr)(prow, pcol));
    } else {
      bgv += -log((bgDistr)(prow, pcol));
    }
  }

  return (fgv + bgv);
}

double evaluateData(const GraphSegInput& gfi, const DigitalSet& ds) {
  double fgv, bgv;
  double rv = gfi.dataWeightValidation *
              regionValue(fgv, bgv, ds, *gfi.dataDistribution.fgDistr,
                          *gfi.dataDistribution.bgDistr);
  return rv;
}

double evaluateRegularization(const GraphSegInput& gfi, const DigitalSet& ds) {
  return GraphFlow::Utils::Energy::elastica(ds, gfi.vradius, gfi.h, gfi.alpha,
                                            gfi.curvatureWeightValidation);
}

double evaluateRegularization(const GraphSegInput& gfi, const DigitalSet& ds,
                              const DigitalSet& belMask) {
  return GraphFlow::Utils::Energy::elastica(ds, gfi.vradius, gfi.h, gfi.alpha,
                                            gfi.curvatureWeightValidation,
                                            belMask);
}

TerminalWeightVector prepareTerminalWeights(const GraphSegInput& gfi,
                                            const DigitalSet& ds,
                                            const DTL2& dtInterior,
                                            const DTL2& dtExterior) {
  TerminalWeightVector twv;

  twv.push_back(new Weight::ForegroundSeed(dtInterior, gfi.optBand, gfi.radius));
  twv.push_back(new Weight::BackgroundSeed(dtExterior, gfi.optBand, gfi.radius));

  if( gfi.dataWeightCandidate==0 ){
    return twv;
  }

  DigitalSet dsFGSeeds(ds.domain());
  dsFGSeeds.insert(gfi.dataDistribution.fgSeeds.begin(),gfi.dataDistribution.fgSeeds.end());
  twv.push_back(new Weight::ForegroundSeed(dsFGSeeds));

  DigitalSet dsBGSeeds(ds.domain());
  dsBGSeeds.insert(gfi.dataDistribution.bgSeeds.begin(),gfi.dataDistribution.bgSeeds.end());
  twv.push_back(new Weight::BackgroundSeed(dsBGSeeds));

  twv.push_back(new Weight::Foreground(*gfi.dataDistribution.fgDistr,
                                  gfi.dataWeightCandidate));
  twv.push_back(new Weight::Background(*gfi.dataDistribution.bgDistr,
                                  gfi.dataWeightCandidate));

  return twv;
}

EdgeWeightVector prepareEdgeWeightVector(const GraphSegInput& gfi,
                                         const DigitalSet& ds,
                                         const cv::Mat& colorImage) {
  EdgeWeightVector ewv(2);
  ewv[0] = new Weight::Curvature(gfi.radius, gfi.h, ds,
                                 gfi.curvatureWeightCandidate);
  ewv[1] = new Weight::Homogeneity(colorImage, gfi.dataWeightCandidate);

  return ewv;
}
}  // namespace GraphFlow::ContourCorrection::Graph