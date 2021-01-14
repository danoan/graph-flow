#include "graph-flow/utils/digital/transform.h"

namespace GraphFlow::Utils::Digital::Transform {
DigitalSet bottomLeftBoundingBoxAtOrigin(const DigitalSet& ds,
                                         const Point border) {
  using namespace DGtal::Z2i;

  assert(ds.size() > 0);

  Point lb, ub;
  ds.computeBoundingBox(lb, ub);

  Point diff = lb;

  Domain newDomain(Point(0, 0), ub - diff + 2 * border);
  DigitalSet newDS(newDomain);
  for (auto it = ds.begin(); it != ds.end(); ++it) {
    newDS.insert(*it - diff + border);
  }

  return newDS;
}
}  // namespace GraphFlow::Utils::Digital::Transform