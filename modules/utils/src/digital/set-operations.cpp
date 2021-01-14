#include "graph-flow/utils/digital/set-operations.h"

namespace GraphFlow::Utils::Digital::SetOperations {
void setDifference(DigitalSet &differenceSet, const DigitalSet &A,
                   const DigitalSet &B) {
  assert(differenceSet.domain().isInside(A.domain().lowerBound()));
  assert(differenceSet.domain().isInside(A.domain().upperBound()));

  differenceSet = A;

  for (auto it = B.begin(); it != B.end(); ++it) {
    differenceSet.erase(*it);
  }
}

Domain DigitalBallIntersection::extendDomain(const DigitalSet &ds, size_t r) {
  return Domain(ds.domain().lowerBound() - Point(r, r),
                ds.domain().upperBound() + Point(r, r));
}

DigitalSet DigitalBallIntersection::extendDS(const DigitalSet &ds, size_t r) {
  Domain extDomain = extendDomain(ds, r);
  DigitalSet temp(extDomain);
  temp = ds;

  return temp;
}

DigitalBallIntersection::DigitalBallIntersection(size_t r, const DigitalSet &intersectWith)
    : _r(r),
      _extDomain(extendDomain(intersectWith, _r)),
      _ds(extendDS(intersectWith, _r)),
      _ball(GraphFlow::Utils::Digital::Shapes::ball(1.0, 0, 0, r)) {}

}  // namespace GraphFlow::Utils::Digital::SetOperations