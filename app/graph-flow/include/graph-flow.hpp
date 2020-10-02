#include "graph-flow.h"

namespace App {

template<class TNeighExplorerIterator>
Candidate selectBestCandidate(TNeighExplorerIterator begin,TNeighExplorerIterator end){
  std::vector<Candidate> candidates;
  for (auto it = begin; it!=end; ++it) {
    candidates.insert(candidates.end(),
                      it->vars.candidatesVector.begin(),
                      it->vars.candidatesVector.end());
  }

  std::sort(candidates.begin(),
            candidates.end(),
            [](const Candidate& c1, const Candidate& c2) {
              return c1.value < c2.value;
            });

  return candidates[0];
}

template<class TNeighborhood>
void graphFlow(const GraphFlowInput &gfi, TNeighborhood &&neighborhood, std::ostream &os, IterationCallback &icb) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;
  using namespace GraphFlow::Core;

  const InputData &id = gfi.inputData;
  DigitalSet ds = gfi.inputDS;

  double lastEnergyValue = Utils::evaluateEnergy(id, ds);
  int itNumber = 0;
  bool execute = true;

  icb(GraphFlowIteration(itNumber, lastEnergyValue, ds, GraphFlowIteration::Init));
  while (execute) {
    Graph::Context context(gfi, ds, neighborhood);
    auto range = magLac::Core::addRange(context.neighborhood.begin(), context.neighborhood.end(), 1);
    auto neighExplorer = createNeighborExplorer<UserVars, Params>(range, context);

    neighExplorer.start(Graph::visitNeighbor(neighExplorer), id.nThreads);

    Candidate bestCandidate = selectBestCandidate(neighExplorer.begin(), neighExplorer.end());

    ds.clear();
    ds.insert(bestCandidate.ds->begin(), bestCandidate.ds->end());
    icb(GraphFlowIteration(itNumber, lastEnergyValue, ds, GraphFlowIteration::Running));

    //Stop conditions
    if (id.iterations==-1) {
      //For unlimited iterations, stop if the current best solution is worst than previous best solution
      if (bestCandidate.value >= lastEnergyValue) execute = false;
    } else {
      if (fabs(bestCandidate.value - lastEnergyValue) < 1e-6) execute = false;
      else if (itNumber >= id.iterations) execute = false;
    }

    lastEnergyValue = bestCandidate.value;
    ++itNumber;
  }

  icb(GraphFlowIteration(itNumber, lastEnergyValue, ds, GraphFlowIteration::End));
}
}