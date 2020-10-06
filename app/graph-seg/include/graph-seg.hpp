#include "graph-seg.h"

namespace App {

template<class TNeighExplorer>
double buildBestSolution(DigitalSet &solution, TNeighExplorer &neighExplorer) {

  std::vector<App::Candidate> allCandidates;
  for (auto it = neighExplorer.begin(); it!=neighExplorer.end(); ++it) {
    allCandidates.insert(allCandidates.end(),
                         it->vars.vectorOfCandidates.begin(),
                         it->vars.vectorOfCandidates.end());
  }

  std::sort(allCandidates.begin(),
            allCandidates.end(),
            [](const App::Candidate &c1, const App::Candidate &c2) {
              return c1.value < c2.value;
            });

  Candidate& bestCandidate = allCandidates[0];
  solution = *bestCandidate.ds;

  return bestCandidate.value;
}

template<class TNeighborhood>
DigitalSet graphSeg(const App::GraphSegInput &gfi, TNeighborhood&& neighborhood, std::ostream &os, App::IterationCallback &icb) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;
  using namespace GraphFlow::Core;

  const App::InputData &id = gfi.inputData;
  DigitalSet ds = gfi.inputDS;

  int itNumber = 0;
  double lastEnergyValue = App::Graph::evaluateData(id, ds, gfi.dataDistribution) + App::Utils::evaluateEnergy(id, ds);
  icb(App::GraphSegIteration(itNumber++, lastEnergyValue, ds, App::GraphSegIteration::Init));


  bool executing = true;
  while (executing) {
    App::Graph::Context context(gfi, ds, neighborhood);
    auto range = magLac::Core::addRange(context.neighborhood.begin(), context.neighborhood.end(), 1);
    auto neighExplorer = App::createNeighborExplorer<App::UserVars, App::Params>(range, context);

    neighExplorer.start(App::Graph::visitNeighbor(neighExplorer), id.nThreads);


    ds.clear();
    double energyValue = buildBestSolution(ds,neighExplorer);


    //Stop conditions
    if (id.iterations==-1) {
      //For unlimited iterations, stop if the current best solution is worst than previous best solution
      if (energyValue >= lastEnergyValue) executing = false;
    } else {
      if (fabs(energyValue - lastEnergyValue) < 1e-6) executing = false;
      else if (itNumber >= id.iterations) executing = false;
    }

    lastEnergyValue = energyValue;
    icb(App::GraphSegIteration(itNumber, lastEnergyValue, ds, App::GraphSegIteration::Running));

    ++itNumber;
  }

  icb(App::GraphSegIteration(itNumber, lastEnergyValue, ds, App::GraphSegIteration::End));

  return ds;
}
}