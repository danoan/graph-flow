#include "graph-flow/utils/digital/misc.h"

namespace GraphFlow::Utils::Digital::Misc {
DTL2 interiorDistanceTransform(const Domain& domain,
                               const DigitalSet& original) {
  return DTL2(domain, original, DGtal::Z2i::l2Metric);
}

DTL2 exteriorDistanceTransform(const Domain& domain,
                               const DigitalSet& original) {
  DigitalSet d(domain);
  d.assignFromComplement(original);

  return DTL2(domain, d, DGtal::Z2i::l2Metric);
}

DigitalSet level(const DTL2& dtL2, int lessThan, int greaterThan) {
  DigitalSet d(dtL2.domain());
  for (auto it = dtL2.domain().begin(); it != dtL2.domain().end(); ++it) {
    if (dtL2(*it) <= lessThan && dtL2(*it) > greaterThan) d.insert(*it);
  }

  return d;
}
}  // namespace GraphFlow::Utils::Digital::Misc