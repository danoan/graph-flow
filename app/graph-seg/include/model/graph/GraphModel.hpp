#include "model/graph/GraphModel.h"


namespace App::Graph{

template<class TComponentExplorer>
typename TComponentExplorer::VisitComponentFunction visitComponent(TComponentExplorer& componentExplorer){
  typedef TComponentExplorer NE;
  typedef typename NE::MyResolver MyResolver;
  typedef typename NE::MyThreadInput MyThreadInput;
  typedef typename NE::ThreadControl ThreadControl;
  typedef typename NE::Context MyContext;

  return
      [](const MyContext& context, MyResolver& resolver, MyThreadInput & ti, ThreadControl& tc)
      {
        std::vector< typename MyContext::IdentifiedComponent > idCVector(1);
        resolver >> idCVector;

        int id = idCVector[0].first;
        const DigitalSet& component = *(idCVector[0].second);

        const App::GraphSegInput& gfi = context.gfi;

        const DigitalSet &ds = context.ds;
        const DigitalSet &background = context.background;
        const cv::Vec3d& avgB = context.avgB;
        const double initialCVB = context.initialCVB;

        const cv::Vec3d& avgF = context.avgF;
        double initialCVF = Utils::DataTerm::chanvese_region_term(component,gfi.cvImg,avgF);

        for(auto blueprint:context.neighborhood){
          DigitalSet candidateDS(ds.domain());
          context.neighborhood.evaluateCandidate(candidateDS, blueprint, component);

          DigitalSet* optimalSet = new DigitalSet(ds.domain());

          if(candidateDS.size()>0){
            DigitalSet partialSolution(candidateDS.domain());
            optimizeConnectedComponent(partialSolution,candidateDS, gfi,avgF,avgB);
            optimalSet->insert(partialSolution.begin(),partialSolution.end());
          }

          DigitalSet newBGDS(ds.domain());
          DigitalSet newFGDS(ds.domain());

          DIPaCUS::SetOperations::setDifference(newBGDS,component,*optimalSet);
          DIPaCUS::SetOperations::setDifference(newFGDS,*optimalSet,component);

          double newCVB = Utils::DataTerm::chanvese_region_term(newBGDS,gfi.cvImg,avgB)
              - Utils::DataTerm::chanvese_region_term(newBGDS,gfi.cvImg,avgF);

          double newCVF = Utils::DataTerm::chanvese_region_term(newFGDS,gfi.cvImg,avgF)
              - Utils::DataTerm::chanvese_region_term(newFGDS,gfi.cvImg,avgB);

          double newCVR = newCVB + newCVF + initialCVF;

          double dataFidelityValue = gfi.inputData.regionalTermWeight*(newCVR);//negative is good
          double elasticaValue = App::Utils::evaluateEnergy(gfi.inputData, *optimalSet);
          double energyValue = dataFidelityValue + elasticaValue;

          ti.vars.vectorOfCandidates.push_back(Candidate{id,optimalSet,energyValue});
        }

        //Insert fg seeds to the current candidate
        //for (auto p:gfi.dataDistribution.fgSeeds) optimalSet->insert(p);

        //Remove bg seeds from the current candidate
        //for (auto pt:gfi.dataDistribution.bgSeeds) optimalSet->erase(pt);
      };
}
}