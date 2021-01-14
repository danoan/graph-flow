#include "graph-flow/utils/digital/types/BeanShape.h"

namespace GraphFlow::Utils::Digital::Shapes {
BeanShape::BeanShape(const double x, const double y, double curvature) {
  this->center = RealPoint(x, y);
  this->r1 = 1.0 / curvature;

  this->a1 = center - RealPoint(3 * this->r1, 0);
  this->c1 = this->a1 + RealPoint(this->r1, 0);
  this->b1 = this->c1 + RealPoint(this->r1, 0);

  this->a2 = this->b1;
  this->c2 = this->a2 + RealPoint(this->r1, 0);
  this->b2 = this->c2 + RealPoint(this->r1, 0);

  this->a3 = this->b2;
  this->c3 = this->a3 + RealPoint(this->r1, 0);
  this->b3 = this->c3 + RealPoint(this->r1, 0);

  this->r2 = 3 * this->r1;
  this->a4 = this->a1;
  this->c4 = this->c2;
  this->b4 = this->c4 + RealPoint(this->r2, 0);

  this->f1 = circle(this->c1, this->r1, true);
  this->f2 = outerCircle(this->c2, this->r1);
  this->f3 = circle(this->c3, this->r1, true);
  this->f4 = circle(this->c4, this->r2, false);

  this->lb = center - RealPoint(this->r2, this->r2);
  this->ub = center + RealPoint(this->r2, this->r1);
}

BeanShape::CirclePredicate BeanShape::circle(const RealPoint& center,
                                             const double radius,
                                             const bool aboveYCenter) {
  double sign = aboveYCenter ? 1.0 : -1.0;
  return [sign, center, radius](const RealPoint& p) {
    return (pow(center[0] - p[0], 2) + pow(center[1] - p[1], 2) -
            pow(radius, 2)) <= 0 &&
           sign * p[1] >= sign * center[1];
  };
}

BeanShape::CirclePredicate BeanShape::outerCircle(const RealPoint& center,
                                                  const double radius) {
  return [center, radius](const RealPoint& p) {
    return (pow(center[0] - p[0], 2) + pow(center[1] - p[1], 2) -
            pow(radius, 2)) >= 0 &&
           p[1] <= center[1];
  };
}

DGtal::Orientation BeanShape::orientation(const RealPoint& aPoint) const {
  double x = aPoint[0];
  double y = aPoint[1];

  bool decisionFlag;
  bool bottomFlag = this->f4(aPoint);

  if (x >= this->a1[0] && x < this->b1[0]) {
    decisionFlag = (this->f1(aPoint) && y >= this->center[1]) ||
                   (bottomFlag && y <= this->center[1]);
  } else if (x >= this->a2[0] && x < this->b2[0]) {
    decisionFlag = this->f2(aPoint) && bottomFlag;
  } else if (x >= this->a3[0] && x < this->b3[0]) {
    decisionFlag = (this->f3(aPoint) && y >= this->center[1]) ||
                   (bottomFlag && y <= this->center[1]);
  } else {
    decisionFlag = false;
  }

  if (decisionFlag)
    return DGtal::Orientation::INSIDE;
  else
    return DGtal::Orientation::OUTSIDE;
}

}  // namespace GraphFlow::Utils::Digital::Shape
