#include "model/graph/GraphModel.h"

namespace App::Graph{

void optimizeConnectedComponent(DigitalSet& solutionSet, const DigitalSet& candidateDS, const App::GraphSegInput& gfi, const cv::Vec3d& avgF, const cv::Vec3d& avgB){
  using namespace DGtal::Z2i;

  Point lb,ub;
  candidateDS.computeBoundingBox(lb,ub);
  Point optBandBorder(gfi.inputData.optBand+1,gfi.inputData.optBand+1);

  Domain reducedDomain(lb-2*optBandBorder,ub+2*optBandBorder);
  const Domain& domain = candidateDS.domain();

  auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(reducedDomain,candidateDS);
  auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(reducedDomain,candidateDS);

  auto ewv = prepareEdgeWeightVector(gfi.inputData,candidateDS,gfi.cvImg);
  auto twv = prepareTerminalWeights(gfi.inputData,dtInterior,dtExterior,gfi.cvImg,candidateDS,avgF,avgB);

  DigitalSet _vertexSet = GraphFlow::Utils::Digital::level(dtInterior,gfi.inputData.optBand,0);
  _vertexSet += GraphFlow::Utils::Digital::level(dtExterior,gfi.inputData.optBand,0);
  DigitalSet vertexSet(domain);
  for(auto p:_vertexSet) if(domain.isInside(p)) vertexSet.insert(p);


  FlowGraph fg(vertexSet,twv,ewv);
  DIPaCUS::SetOperations::setDifference(solutionSet,candidateDS,vertexSet);
  solutionSet.insert(fg.sourceNodes.begin(), fg.sourceNodes.end());

  for(auto ew:ewv) delete ew;
  for(auto tw:twv) delete tw;
}

double evaluateData(const InputData& id,const DigitalSet& ds, const cv::Mat& cvImgIn)
{
  return id.regionalTermWeight*Utils::DataTerm::chanvese(id,ds,cvImgIn);
}

TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const cv::Mat& cvImgIn, const DigitalSet& ds, const cv::Vec3d& avgF, const cv::Vec3d& avgB)
{
  TerminalWeightVector twv(4);
  twv[0] = new Weight::ForegroundSeed(dtInterior,id.optBand,id.radius);
  twv[1] = new Weight::BackgroundSeed(dtExterior,id.optBand,id.radius);

  twv[2] = new Weight::ForegroundChanVese(cvImgIn,avgF,id.regionalTermGraphWeight);
  twv[3] = new Weight::BackgroundChanVese(cvImgIn,avgB,id.regionalTermGraphWeight);

  return twv;
}

EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage)
{
  EdgeWeightVector ewv(1);
  ewv[0] = new Weight::Curvature(id.radius,id.h,ds,id.curvatureTermGraphWeight);
  return ewv;
}
}