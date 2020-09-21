#include "model/graph/GraphModel.h"


namespace App::Graph{

template<class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer& neighExplorer){
  typedef TNeighborhoodExplorer NE;
  typedef typename NE::MyResolver MyResolver;
  typedef typename NE::MyThreadInput MyThreadInput;
  typedef typename NE::ThreadControl ThreadControl;
  typedef typename NE::Context MyContext;

  return
      [](const MyContext& context, MyResolver& resolver, MyThreadInput & ti, ThreadControl& tc)
      {
        MorphologyNeighborhood::VectorOfBlueprints c1(1);
        resolver >> c1;

        const MorphologyNeighborhood::Blueprint& blueprint = c1[0];
        const App::GraphSegInput& gfi = context.gfi;

        int nc = context.connectedComponents.size();
        for(int id=0;id<nc;++id) {
          const DigitalSet &ds = *context.connectedComponents[id];

          DigitalSet candidateDS(ds.domain());
          context.neighborhood.evaluateCandidate(candidateDS, blueprint, ds);

          //Remove bg seeds from the current candidate
          for (auto pt:gfi.dataDistribution.bgSeeds) candidateDS.erase(pt);

          if (candidateDS.empty()) continue;

          DigitalSet *optimalSet = optimizeConnectedComponent(candidateDS, gfi);
          if (optimalSet->empty()) {
            delete optimalSet;
            continue;
          }

          DigitalSet newFG(ds.domain());
          DIPaCUS::SetOperations::setDifference(newFG,*optimalSet,ds);

          DigitalSet newBG(ds.domain());
          DIPaCUS::SetOperations::setDifference(newBG,ds,*optimalSet);

          double f = diffDataValue(newFG,gfi.dataDistribution,true) - diffDataValue(newFG,gfi.dataDistribution,false);
          double b = diffDataValue(newBG,gfi.dataDistribution,false) - diffDataValue(newBG,gfi.dataDistribution,true);

          double dataFidelityValue = gfi.inputData.regionalTermWeight*(f + b);
          double elasticaValue = App::Utils::evaluateEnergy(gfi.inputData, *optimalSet);
          double energyValue = dataFidelityValue + elasticaValue;

          ti.vars.vectorOfCandidates.push_back(Candidate{id,optimalSet,energyValue});
        }

      };
}
}