#include "graph-seg.h"

namespace App {
DigitalSet graphSeg(const App::GraphSegInput &gfi, std::ostream &os, App::IterationCallback &icb) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;
  using namespace GraphFlow::Core;

  const App::InputData &id = gfi.inputData;
  DigitalSet ds = gfi.inputDS;

  App::Graph::MorphologyNeighborhood neighborhood(App::Graph::MorphologyNeighborhood::MorphologyElement::CIRCLE,
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
    buildBestSolution(ds,neighExplorer);

    //Insert fg seeds to the current candidate
    //for (auto p:gfi.dataDistribution.fgSeeds) ds.insert(p);

    double dataFidelityValue = Graph::evaluateData(gfi.inputData, ds, gfi.dataDistribution);
    double elasticaValue = App::Utils::evaluateEnergy(gfi.inputData, ds);
    double energyValue = dataFidelityValue + elasticaValue;

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