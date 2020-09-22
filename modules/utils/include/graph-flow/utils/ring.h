#ifndef GRAPH_FLOW_MODULES_UTILS_INCLUDE_GRAPH_FLOW_UTILS_RING_H_
#define GRAPH_FLOW_MODULES_UTILS_INCLUDE_GRAPH_FLOW_UTILS_RING_H_

#include <functional>
#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Shapes.h>

namespace GraphFlow::Utils::Shapes{
class RingShape
{
 public:
  typedef DGtal::Z2i::RealPoint RealPoint;

 private:
  typedef DGtal::Z2i::Point Point;

  typedef std::function<bool(const RealPoint& p)> CirclePredicate;

 public:
  RingShape(const double x, const double y, const double smallR, const double bigR);

  DGtal::Orientation orientation(const RealPoint& aPoint) const;

  RealPoint getLowerBound() const { return lb; }
  RealPoint getUpperBound() const { return ub; }

 private:
  CirclePredicate circle(const RealPoint& center, const double radius);

 public:
  RealPoint lb,ub;

  CirclePredicate smallCircle;
  CirclePredicate bigCircle;
};

DGtal::Z2i::DigitalSet ringMask(const DGtal::Z2i::Domain& domain,double smallR, double bigR,int border);
}

#endif //GRAPH_FLOW_MODULES_UTILS_INCLUDE_GRAPH_FLOW_UTILS_RING_H_
