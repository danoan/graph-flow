#include "model/graph/GraphModel.h"

namespace App::Graph{

double diffDataValue(const DigitalSet& diffSet,const App::Image::DataDistribution& DD,bool fg){
  const cv::Mat& img = DD.segResultImg;

  const App::Image::CVMatDistribution* distr;
  if(fg) distr = DD.fgDistr;
  else distr = DD.bgDistr;

  double v=0;
  for(auto p:diffSet)
  {
    int prow=img.rows-p[1];
    int pcol=p[0];

    v+=-log( (*distr)(prow,pcol) );
  }

  return v;
}

DigitalSet* optimizeConnectedComponent(const DigitalSet& candidateDS, const App::GraphSegInput& gfi){
  Point lb,ub;
  candidateDS.computeBoundingBox(lb,ub);
  Point optBandBorder(gfi.inputData.optBand+1,gfi.inputData.optBand+1);

  Domain reducedDomain(lb-2*optBandBorder,ub+2*optBandBorder);
  const Domain& domain = candidateDS.domain();

  auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(reducedDomain,candidateDS);
  auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(reducedDomain,candidateDS);

  auto ewv = prepareEdgeWeightVector(gfi.inputData,candidateDS,gfi.dataDistribution.segResultImg);
  auto twv = prepareTerminalWeights(gfi.inputData,dtInterior,dtExterior,gfi.dataDistribution,candidateDS);

  DigitalSet _vertexSet = GraphFlow::Utils::Digital::level(dtInterior,gfi.inputData.optBand,0);
  _vertexSet += GraphFlow::Utils::Digital::level(dtExterior,gfi.inputData.optBand,0);
  DigitalSet vertexSet(domain);
  for(auto p:_vertexSet) if(domain.isInside(p)) vertexSet.insert(p);


  FlowGraph fg(vertexSet,twv,ewv);
  DigitalSet* solutionSet = new DigitalSet(domain);
  DIPaCUS::SetOperations::setDifference(*solutionSet,candidateDS,vertexSet);
  solutionSet->insert(fg.sourceNodes.begin(), fg.sourceNodes.end());

  for(auto ew:ewv) delete ew;
  for(auto tw:twv) delete tw;

  return solutionSet;
}

double regionValue(double& fgv, double& bgv,const DigitalSet& ds, const App::Image::CVMatDistribution& fgDistr, const App::Image::CVMatDistribution& bgDistr)
{
  const cv::Mat& img = fgDistr.img;
  bgv=0;
  fgv=0;
  for(auto p:ds.domain())
  {
    int prow=img.rows-p[1]-1;
    int pcol=p[0];

    if(ds(p))
    {
      fgv+=-log( (fgDistr)(prow,pcol) );
    }else
    {
      bgv+=-log( (bgDistr)(prow,pcol) );
    }
  }

  return (fgv+bgv);
}

double evaluateData(const InputData& id,const DigitalSet& ds, const App::Image::DataDistribution& DD)
{
  double fgv,bgv;
  double rv = id.regionalTermWeight*regionValue(fgv,bgv,ds,*DD.fgDistr,*DD.bgDistr);
  return rv;
}

TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const App::Image::DataDistribution& DD, const DigitalSet& ds)
{
  TerminalWeightVector twv(4);
  twv[0] = new Weight::ForegroundSeed(dtInterior,id.optBand,id.radius);
  twv[1] = new Weight::BackgroundSeed(dtExterior,id.optBand,id.radius);

  twv[2] = new Weight::Foreground(*DD.fgDistr,id.regionalTermWeight);
  twv[3] = new Weight::Background(*DD.bgDistr,id.regionalTermWeight);

  return twv;
}

EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage)
{
  EdgeWeightVector ewv(2);
  ewv[0] = new Weight::Curvature(id.radius,id.h,ds,id.curvatureTermWeight);
  ewv[1] = new Weight::Homogeneity(colorImage,1.0);

  return ewv;
}
}