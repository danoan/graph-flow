#ifndef GRAPH_FLOW_UTILS_ENERGY_H
#define GRAPH_FLOW_UTILS_ENERGY_H

#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
#include <DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h>
#include <DGtal/geometry/curves/estimation/SegmentComputerEstimators.h>
#include <DGtal/geometry/surfaces/estimation/IIGeometricFunctors.h>
#include <DGtal/geometry/surfaces/estimation/IntegralInvariantVolumeEstimator.h>
#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/derivates/Misc.h>

namespace GraphFlow::Utils::Energy {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::KSpace KSpace;
typedef DGtal::Z2i::Point Point;
typedef DGtal::Z2i::Curve::ConstIterator CurveIterator;
typedef std::set<Point> PointSet;

void localLength(std::vector<double>& ev, const KSpace& kspace,
                 CurveIterator itb, CurveIterator ite, double h);

void curvature(std::vector<double>& ev, const KSpace& kspace, CurveIterator itb,
               CurveIterator ite, const DigitalSet& digShape,
               double estimationRadius, double h);

double elastica(CurveIterator begin, CurveIterator end,
                const DigitalSet& ds, double estimationRadius, double h,
                double alpha, double beta);
                
double elastica(const DigitalSet& ds, double estimationRadius, double h,
                double alpha, double beta);
}  // namespace GraphFlow::Utils::Energy

#endif  // GRAPH_FLOW_UTILS_ENERGY_H
