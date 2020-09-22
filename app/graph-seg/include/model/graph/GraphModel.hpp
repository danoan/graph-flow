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
        RandomNeighborhood::VectorOfBlueprints c1(1);
        resolver >> c1;

        const RandomNeighborhood::Blueprint& blueprint = c1[0];
        const App::GraphSegInput& gfi = context.gfi;

        const DigitalSet &ds = context.ds;

        DigitalSet candidateDS(ds.domain());
        context.neighborhood.evaluateCandidate(candidateDS, blueprint, ds);

        std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
        DIPaCUS::Misc::getConnectedComponents(vcc,candidateDS);

        DigitalSet* optimalSet = new DigitalSet(candidateDS.domain());
        for(auto cc:vcc){
          DigitalSet ccDS(candidateDS.domain());
          ccDS.insert(cc.begin(),cc.end());

          DigitalSet partialSolution(candidateDS.domain());
          optimizeConnectedComponent(partialSolution,ccDS, gfi);
          optimalSet->insert(partialSolution.begin(),partialSolution.end());
        }

        //Insert fg seeds to the current candidate
        for (auto p:gfi.dataDistribution.fgSeeds) optimalSet->insert(p);

        //Remove bg seeds from the current candidate
        for (auto pt:gfi.dataDistribution.bgSeeds) optimalSet->erase(pt);


        double dataFidelityValue = App::Graph::evaluateData(gfi.inputData,*optimalSet,gfi.dataDistribution);
        double elasticaValue = App::Utils::evaluateEnergy(gfi.inputData, *optimalSet);
        double energyValue = dataFidelityValue + elasticaValue;

        ti.vars.vectorOfCandidates.push_back(Candidate{optimalSet,energyValue});

      };
}
}