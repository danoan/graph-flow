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
        typename MyContext::Neighborhood::VectorOfBlueprints c1(1);
        resolver >> c1;

        typename MyContext::Neighborhood::Blueprint& blueprint = c1[0];
        const App::GraphSegInput& gfi = context.gfi;
        const DigitalSet& ds = context.ds;


        DigitalSet candidateDS(ds.domain());
        context.neighborhood.evaluateCandidate(candidateDS,blueprint,ds);

        //Insert fg seeds to the current candidate
        for(auto p:gfi.dataDistribution.fgSeeds) candidateDS.insert(p);
        //Remove bg seeds from the current candidate
        for(auto pt:gfi.dataDistribution.bgSeeds) candidateDS.erase(pt);

        if(candidateDS.empty()) return;

        DigitalSet* optimalSet = optimizeConnectedComponent(candidateDS,gfi);
        if(optimalSet->empty()){
          delete optimalSet;
          return;
        }

        double dataFidelityValue= evaluateData(gfi.inputData,ds,gfi.dataDistribution);
        double elasticaValue = App::Utils::evaluateEnergy(gfi.inputData,*optimalSet);
        double energyValue = dataFidelityValue + elasticaValue;

        ti.vars.vectorOfCandidates.push_back( Candidate{optimalSet,energyValue} );


      };
}
}