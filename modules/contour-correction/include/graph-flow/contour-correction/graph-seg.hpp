#include "graph-seg.h"

namespace GraphFlow::ContourCorrection {

template <class TNeighExplorer>
double buildBestSolution(DigitalSet &solution, TNeighExplorer &neighExplorer) {
  std::vector<Candidate> allCandidates;
  for (auto it = neighExplorer.begin(); it != neighExplorer.end(); ++it) {
    allCandidates.insert(allCandidates.end(),
                         it->mutableData.candidatesVector.begin(),
                         it->mutableData.candidatesVector.end());
  }

  std::sort(allCandidates.begin(), allCandidates.end(),
            [](const Candidate &c1, const Candidate &c2) {
              return c1.value < c2.value;
            });

  Candidate &bestCandidate = allCandidates[0];
  solution = *bestCandidate.ds;

  return bestCandidate.value;
}

template <class TNeighborhood>
DigitalSet graphSeg(const GraphSegInput &gfi, TNeighborhood &&neighborhood,
                    std::ostream &os, IterationCallback &icb) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;
  using namespace GraphFlow::Core;

  DigitalSet ds = gfi.inputDS;

  int itNumber = 0;
  double lastEnergyValue =
      Graph::evaluateData(gfi, ds) + Graph::evaluateRegularization(gfi, ds);
  icb(GraphSegIteration(itNumber++, lastEnergyValue, ds,
                        GraphSegIteration::Init));

  auto range =
      magLac::Core::addRange(neighborhood.begin(), neighborhood.end(), 1);

  bool executing = true;
  while (executing) {
    Graph::Context context(gfi, ds, neighborhood);

    auto neighExplorer = createNeighborExplorer<MyThreadData>(*range, context);

    neighExplorer.start(Graph::visitNeighbor(neighExplorer), gfi.nThreads);

    ds.clear();
    double energyValue = buildBestSolution(ds, neighExplorer);

    // Stop conditions
    if (gfi.iterations == -1) {
      // For unlimited iterations, stop if the current best solution is worst
      // than previous best solution
      if (energyValue >= lastEnergyValue) executing = false;
    } else {
      if (gfi.tolerance >= 0) {
        if (fabs(lastEnergyValue - energyValue) <= gfi.tolerance) {
          executing = false;
        }
      }
      if (itNumber >= gfi.iterations) executing = false;
    }

    lastEnergyValue = energyValue;
    icb(GraphSegIteration(itNumber, lastEnergyValue, ds,
                          GraphSegIteration::Running));

    ++itNumber;
  }

  icb(GraphSegIteration(itNumber, lastEnergyValue, ds, GraphSegIteration::End));

  return ds;
}
}  // namespace GraphFlow::ContourCorrection