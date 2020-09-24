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

  bool update=true;
  int tries=0;
  int itNumber = 0;
  bool executing = true;
  DigitalSet solution(ds.domain());
  double lastEnergyValue = App::Graph::evaluateData(id, ds, gfi.dataDistribution) + App::Utils::evaluateEnergy(id, ds);
  icb(App::GraphSegIteration(itNumber, lastEnergyValue, ds, App::GraphSegIteration::Init));
  while (executing) {
    App::Graph::Context context(gfi, ds, neighborhood);


    auto range = magLac::Core::addRange(context.connectedComponents.begin(), context.connectedComponents.end(), 1);
    auto componentExplorer = App::createComponentExplorer<App::UserVars, App::Params>(range, context);
    componentExplorer.start(App::Graph::visitComponent(componentExplorer), id.nThreads);

    solution.clear();
    buildBestSolution(solution,componentExplorer);

    double dataFidelityValue = App::Graph::evaluateData(gfi.inputData,solution,gfi.dataDistribution);
    double elasticaValue = App::Utils::evaluateEnergy(gfi.inputData, solution);
    double energyValue = dataFidelityValue + elasticaValue;

    //Stop conditions
    if (id.iterations==-1) {
      //For unlimited iterations, stop if the current best solution is worst than previous best solution
      tries++;
      std::cout << tries << ":" << energyValue << ":" << lastEnergyValue << std::endl;
      if (energyValue >= lastEnergyValue){
        if(tries>=20) executing = false;
        else update=false;
      }else{
        update=true;
      }

    } else {
      if (fabs(energyValue - lastEnergyValue) < 1e-6) executing = false;
      else if (itNumber >= id.iterations) executing = false;
    }

    if(update){
      ds = solution;
      lastEnergyValue = energyValue;
      icb(App::GraphSegIteration(itNumber, lastEnergyValue, ds, App::GraphSegIteration::Running));

      ++itNumber;
      tries=0;
    }else{
      update=true;
    }
  }

  icb(App::GraphSegIteration(itNumber, lastEnergyValue, ds, App::GraphSegIteration::End));

  return ds;
}
}