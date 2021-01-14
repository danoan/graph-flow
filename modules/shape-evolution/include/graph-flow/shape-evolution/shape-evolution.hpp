#include "shape-evolution.h"

namespace GraphFlow::ShapeEvolution {

template <class TNeighExplorerIterator>
Candidate selectBestCandidate(TNeighExplorerIterator begin,
                              TNeighExplorerIterator end) {
  std::vector<Candidate> candidates;
  for (auto it = begin; it != end; ++it) {
    candidates.insert(candidates.end(),
                      it->mutableData.candidatesVector.begin(),
                      it->mutableData.candidatesVector.end());
  }

  std::sort(candidates.begin(), candidates.end(),
            [](const Candidate &c1, const Candidate &c2) {
              return c1.value < c2.value;
            });

  return candidates[0];
}

template <class TNeighborhood>
void graphFlow(const GraphFlowInput &gfi, TNeighborhood &&neighborhood,
               std::ostream &os, IterationCallback &icb) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;
  using namespace GraphFlow::Core;

  DigitalSet ds = gfi.inputDS;

  double lastEnergyValue =
      Energy::elastica(ds, gfi.vradius, gfi.h, gfi.alpha, gfi.beta);
  int itNumber = 0;
  icb(GraphFlowIteration(itNumber++, lastEnergyValue, ds,
                         GraphFlowIteration::Init));

  auto range =
      magLac::Core::addRange(neighborhood.begin(), neighborhood.end(), 1);

  bool execute = true;
  while (execute) {
    Graph::Context context(gfi, ds, neighborhood);

    auto neighExplorer = createNeighborExplorer<MyThreadData>(*range, context);
    neighExplorer.start(Graph::visitNeighbor(neighExplorer), gfi.nThreads);

    Candidate bestCandidate =
        selectBestCandidate(neighExplorer.begin(), neighExplorer.end());

    ds.clear();
    ds.insert(bestCandidate.ds->begin(), bestCandidate.ds->end());
    icb(GraphFlowIteration(itNumber, lastEnergyValue, ds,
                           GraphFlowIteration::Running));

    // Stop conditions
    if (gfi.iterations == -1) {
      // For unlimited iterations, stop if the current best solution is worst
      // than previous best solution
      if (bestCandidate.value >= lastEnergyValue) execute = false;
    } else {
      if (gfi.tolerance >= 0) {
        if (fabs(lastEnergyValue - bestCandidate.value) <= gfi.tolerance) {
          execute = false;
        }
      }

      if (itNumber >= gfi.iterations) execute = false;
    }

    lastEnergyValue = bestCandidate.value;
    ++itNumber;
  }

  icb(GraphFlowIteration(itNumber, lastEnergyValue, ds,
                         GraphFlowIteration::End));
}
}  // namespace GraphFlow::ShapeEvolution