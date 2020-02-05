#ifndef GRAPH_FLOW_UTILS_ENERGY_H
#define GRAPH_FLOW_UTILS_ENERGY_H

#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/derivates/Misc.h>

#include <geoc/api/gridCurve/Length.hpp>
#include <geoc/api/gridCurve/Curvature.hpp>
#include <geoc/estimator/adaptable/curvature/II.hpp>

namespace GraphFlow::Utils::Energy
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef DGtal::Z2i::Domain Domain;
    typedef DGtal::Z2i::Point Point;
    typedef std::set<Point> PointSet;

    double elastica(const DigitalSet& ds,double ballRadius,double h,double alpha);
    double sElastica(const DigitalSet& ds,double ballRadius,double h,double alpha);
}

#endif //GRAPH_FLOW_UTILS_ENERGY_H
