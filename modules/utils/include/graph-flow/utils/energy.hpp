#include <graph-flow/utils/energy.h>

namespace GraphFlow::Utils::Energy{
template<class TCurveIterator>
double elastica(TCurveIterator begin, TCurveIterator end,const DigitalSet& ds, double ballRadius,double h,double alpha,double beta){
  using namespace DGtal::Z2i;
  using namespace GEOC::API::GridCurve;

  const Domain& domain = ds.domain();
  KSpace kspace;
  kspace.init(domain.lowerBound(),domain.upperBound(),true);

  double value=0;

  Length::EstimationsVector lengthEV;
  Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(kspace,begin,end,lengthEV,h,NULL);

  GEOC::Estimator::Standard::IICurvatureExtraData iiData(true,ballRadius);
  Curvature::EstimationsVector curvatureEV;
  GEOC::Estimator::Standard::IICurvature(ds,begin,end,curvatureEV,h,&iiData);

  for(int i=0;i<curvatureEV.size();++i)
  {
    value+=alpha*lengthEV[i] + beta*pow(curvatureEV[i],2)*lengthEV[i];
  }

  return value;
}
}