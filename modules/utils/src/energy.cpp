#include "graph-flow/utils/energy.h"

namespace GraphFlow::Utils::Energy {

void localLength(std::vector<double>& ev, const KSpace& kspace,
                 CurveIterator itb, CurveIterator ite, double h) {
  using namespace DGtal::Z2i;

  // Creating a range for points from the GridCurve
  typedef DGtal::functors::SCellToPoint<DGtal::Z2i::KSpace> AdapterFunctor;
  typedef DGtal::ConstRangeAdapter<CurveIterator, AdapterFunctor, KSpace::Point>
      RangeAdapter;

  AdapterFunctor myFunctor(kspace);
  RangeAdapter range(itb, ite, myFunctor);

  // Initializing the tangent estimator
  typedef DGtal::ArithmeticalDSSComputer<RangeAdapter::ConstIterator, int, 4>
      SegmentComputer;
  typedef DGtal::TangentFromDSSEstimator<SegmentComputer> SCEstimator;
  typedef DGtal::PointVector<2, double> TangentVector;

  std::vector<TangentVector> tangentEstimations;
  SegmentComputer sc;
  SCEstimator f;

  DGtal::MostCenteredMaximalSegmentEstimator<SegmentComputer, SCEstimator>
      MCMDSSTangentEstimator(sc, f);

  MCMDSSTangentEstimator.init(h, range.begin(), range.end());
  MCMDSSTangentEstimator.eval(range.begin(), range.end(),
                              std::back_inserter(tangentEstimations));

  int i = 0;
  for (auto it = itb; it != ite; ++it, ++i) {
    ev.push_back(
        h * 1.0 /
        (fabs(tangentEstimations[i][0]) + fabs(tangentEstimations[i][1])));
  }
}

void curvature(std::vector<double>& ev, const KSpace& kspace, CurveIterator itb,
               CurveIterator ite, const DigitalSet& digShape,
               double estimationRadius, double h) {
  typedef DGtal::functors::IICurvatureFunctor<DGtal::Z2i::Space>
      MyIICurvatureFunctor;
  typedef DGtal::IntegralInvariantVolumeEstimator<KSpace, DigitalSet,
                                                  MyIICurvatureFunctor>
      MyIICurvatureEstimator;
  typedef MyIICurvatureFunctor::Value Value;

  /// Functor used to convert volume -> curvature
  MyIICurvatureFunctor curvatureFunctor;
  curvatureFunctor.init(h, estimationRadius);

  MyIICurvatureEstimator curvatureEstimator(curvatureFunctor);
  /// Setting a KSpace and a predicate on the object to evaluate
  curvatureEstimator.attach(kspace, digShape);

  /// Setting the digital radius of the convolution kernel
  curvatureEstimator.setParams(estimationRadius / h);

  /// Initialisation for a given h
  curvatureEstimator.init(h, itb, ite);

  /// output iterator for results of Integral Invariant
  std::back_insert_iterator<std::vector<Value> > resultsIt(ev);

  /// Computation
  curvatureEstimator.eval(itb, ite, resultsIt);
}

double elastica(CurveIterator begin, CurveIterator end, const DigitalSet& ds,
                double estimationRadius, double h, double alpha, double beta) {
  const Domain& domain = ds.domain();
  KSpace kspace;
  kspace.init(domain.lowerBound(), domain.upperBound(), true);

  double value = 0;
  std::vector<double> lengthEV;
  localLength(lengthEV, kspace, begin, end, h);

  std::vector<double> curvatureEV;
  curvature(curvatureEV, kspace, begin, end, ds, estimationRadius, h);

  for (int i = 0; i < curvatureEV.size(); ++i) {
    value += alpha * lengthEV[i] + beta * pow(curvatureEV[i], 2) * lengthEV[i];
  }

  return value;
}

double elastica(const DigitalSet& ds, double ballRadius, double h, double alpha,
                double beta) {
  using namespace DGtal::Z2i;
  KSpace kspace;
  kspace.init(ds.domain().lowerBound(), ds.domain().upperBound(), true);

  DGtal::SurfelAdjacency<2> sadj(true);
  std::vector<std::vector<DGtal::Z2i::SCell> > vscells;

  DGtal::Surfaces<KSpace>::extractAll2DSCellContours(vscells, kspace, sadj, ds);

  double elasticaValue = 0;
  for (auto v : vscells) {
    Curve curve;
    curve.initFromSCellsVector(v);
    elasticaValue +=
        elastica(curve.begin(), curve.end(), ds, ballRadius, h, alpha, beta);
  }

  return elasticaValue;
}

}  // namespace GraphFlow::Utils::Energy