#include "graph-seg.h"


DigitalSet graphSeg(const GraphSegInput& gfi, std::ostream& os, IterationCallback& icb)
{
    using namespace DGtal::Z2i;
    using namespace GraphFlow::Utils;
    using namespace GraphFlow::Core;
    
    const InputData& id = gfi.inputData;
    DigitalSet ds = gfi.inputDS;

    StandardModel::MorphologyNeighborhood neighborhood(StandardModel::MorphologyNeighborhood::MorphologyElement::CIRCLE,id.neighborhoodSize);
    StandardModel::HardConstraintVector hcv;

    double lastEnergyValue= StandardModel::evaluateData(id,ds,gfi.dataDistribution) + evaluateEnergy(id,ds);
    int i=0;
    while(true)
    {
        icb(GraphSegIteration(i,lastEnergyValue,ds));
        if(i==id.iterations) break;

        StandardModel::Context context(gfi,ds,hcv,neighborhood);
        auto range = magLac::Core::addRange(context.neighborhood.begin(),context.neighborhood.end(),1);
        auto neighExplorer = createNeighborExplorer<UserVars,Params>(range,context);


        neighExplorer.start(StandardModel::visitNeighbor(neighExplorer),id.nThreads);
        
        //Select best solution
        std::vector<UserVars::EvaluationPair> evaluationPairs;
        for(auto it=neighExplorer.begin();it!=neighExplorer.end();++it)
        {
            evaluationPairs.insert(evaluationPairs.end(),
                                   it->vars.epVector.begin(),
                                   it->vars.epVector.end());
        }
        
        std::sort(evaluationPairs.begin(),evaluationPairs.end(),[](const UserVars::EvaluationPair& ep1, const UserVars::EvaluationPair&  ep2){ return ep1.second < ep2.second;});
        
        const DigitalSet* bestDS = evaluationPairs[0].first;
        ds.clear();
        ds.insert(bestDS->begin(),bestDS->end());
        
        //Stop conditions
        if(id.iterations==-1)
        {
            //For unlimited iterations, stop if the current best solution is worst than previous best solution
            if( evaluationPairs[0].second > lastEnergyValue ) break;
        }
        else
        {
            if( fabs(evaluationPairs[0].second-lastEnergyValue) < 1e-6 ) break;
        }
        
        lastEnergyValue=evaluationPairs[0].second;
        ++i;
    }

    return ds;
}
