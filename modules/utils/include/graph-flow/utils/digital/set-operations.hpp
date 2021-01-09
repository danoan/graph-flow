#include "graph-flow/utils/digital/set-operations.h"

namespace GraphFlow::Utils::Digital::SetOperations {

template <class TPointSet>
void setIntersection(TPointSet &digitalIntersection, const DigitalSet &A,
                     const DigitalSet &B) {
  for (auto it = A.begin(); it != A.end(); ++it) {
    if (B(*it)) digitalIntersection.insert(*it);
  }
}

template <class TPointSet>
void setIntersection(TPointSet &digitalIntersection, const DigitalSet &A,
                     const DigitalSet &B, const Point &translation) {
  Point tp;
  for (auto it = A.begin(); it != A.end(); ++it) {
    tp = *it + translation;
    if (B(tp)) digitalIntersection.insert(tp);
  }
}
}  // namespace GraphFlow::Utils::Digital::SetOperations