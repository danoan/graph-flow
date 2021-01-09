#include "graph-flow/utils/digital/contour.h"

namespace GraphFlow::Utils::Digital::Contour {
template <typename TNeighborhood>
void digitalBoundary(DigitalSet &boundaryDS, const DigitalSet &originalDS,
                     size_t thickness) {
  typedef TNeighborhood NeighborhoodPredicate;
  typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

  DigitalSet workingSet = originalDS;
  DigitalSet lastInclusion(workingSet.domain());

  DigitalSetInserter inserter(lastInclusion);
  while (thickness > 0) {
    NeighborhoodPredicate NP(workingSet);
    std::remove_copy_if(originalDS.begin(), originalDS.end(), inserter, NP);

    for (auto it = lastInclusion.begin(); it != lastInclusion.end(); ++it)
      workingSet.erase(*it);
    boundaryDS.insert(lastInclusion.begin(), lastInclusion.end());
    lastInclusion.clear();

    --thickness;
  }
}
}  // namespace GraphFlow::Utils::Digital::Contour