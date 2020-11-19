#include "graph-flow/image-segmentation/model/graph/GraphModel.h"

namespace GraphFlow::ImageSegmentation::Graph {

DigitalSet* optimizeConnectedComponent(const GraphSegInput& gfi,
                                       const DigitalSet& candidateDS) {
  Point lb, ub;
  candidateDS.computeBoundingBox(lb, ub);
  Point optBandBorder(gfi.optBand + 1, gfi.optBand + 1);

  Domain reducedDomain(lb - 2 * optBandBorder, ub + 2 * optBandBorder);
  const Domain& domain = candidateDS.domain();

  auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(
      reducedDomain, candidateDS);
  auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(
      reducedDomain, candidateDS);

  auto ewv = prepareEdgeWeightVector(gfi, candidateDS,
                                     gfi.dataDistribution.segResultImg);

  auto twv = prepareTerminalWeights(gfi, candidateDS, dtInterior, dtExterior);

  DigitalSet _vertexSet =
      GraphFlow::Utils::Digital::level(dtInterior, gfi.optBand, 0);
  _vertexSet += GraphFlow::Utils::Digital::level(dtExterior, gfi.optBand, 0);
  DigitalSet vertexSet(domain);
  for (auto p : _vertexSet)
    if (domain.isInside(p)) vertexSet.insert(p);

  FlowGraph fg(vertexSet, twv, ewv);
  DigitalSet* solutionSet = new DigitalSet(domain);
  DIPaCUS::SetOperations::setDifference(*solutionSet, candidateDS, vertexSet);
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
  double rv = gfi.regionalTermWeight *
              regionValue(fgv, bgv, ds, *gfi.dataDistribution.fgDistr,
                          *gfi.dataDistribution.bgDistr);
  return rv;
}

double evaluateRegularization(const GraphSegInput& gfi, const DigitalSet& ds) {
  return GraphFlow::Utils::Energy::elasticaIndependentComponents(
      ds, gfi.vradius, gfi.h, gfi.alpha, gfi.curvatureTermWeight);
}

TerminalWeightVector prepareTerminalWeights(const GraphSegInput& gfi,
                                            const DigitalSet& ds,
                                            const DTL2& dtInterior,
                                            const DTL2& dtExterior) {
  TerminalWeightVector twv(4);
  twv[0] = new Weight::ForegroundSeed(dtInterior, gfi.optBand, gfi.radius);
  twv[1] = new Weight::BackgroundSeed(dtExterior, gfi.optBand, gfi.radius);

  twv[2] = new Weight::Foreground(*gfi.dataDistribution.fgDistr, gfi.regionalTermWeight);
  twv[3] = new Weight::Background(*gfi.dataDistribution.bgDistr, gfi.regionalTermWeight);

  return twv;
}

EdgeWeightVector prepareEdgeWeightVector(const GraphSegInput& gfi,
                                         const DigitalSet& ds,
                                         const cv::Mat& colorImage) {
  EdgeWeightVector ewv(2);
  ewv[0] =
      new Weight::Curvature(gfi.radius, gfi.h, ds, gfi.curvatureTermWeight);
  ewv[1] = new Weight::Homogeneity(colorImage, 1.0);

  return ewv;
}
}  // namespace GraphFlow::ImageSegmentation::Graph