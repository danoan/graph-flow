#include "graph-seg.h"

namespace App {
DigitalSet graphSeg(const App::GraphSegInput &gfi, std::ostream &os, App::IterationCallback &icb) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;
  using namespace GraphFlow::Core;

  const App::InputData &id = gfi.inputData;
  DigitalSet ds = gfi.inputDS;

  App::Graph::RandomNeighborhood neighborhood(App::Graph::RandomNeighborhood::MorphologyElement::CIRCLE,
                                                  id.neighborhoodSize);

  int itNumber = 0;
  bool executing = true;
  double lastEnergyValue = App::Graph::evaluateData(id, ds, gfi.dataDistribution) + App::Utils::evaluateEnergy(id, ds);
  icb(App::GraphSegIteration(itNumber, lastEnergyValue, ds, App::GraphSegIteration::Init));
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