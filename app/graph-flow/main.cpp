#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/single/Combinator.hpp"
#include "magLac/core/multithread/Trigger.h"
#include "magLac/core/multithread/ThreadInput.h"

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/Neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/core/Neighborhood/RandomNeighborhood.h>
#include <graph-flow/core/WeightFunctionInterface.h>

#include <graph-flow/utils/digital.h>
#include <graph-flow/utils/display.h>
#include <graph-flow/utils/timer.h>
#include <graph-flow/utils/energy.h>

#include "InputData.h"
#include "InputReader.h"

using namespace DGtal::Z2i;
using namespace GraphFlow::Core;
using namespace GraphFlow::Utils;

struct UserVars
{
    typedef std::pair<FlowGraph*,double> EvaluationPair;

    void restart(){};
    std::vector<EvaluationPair> epVector;
};

struct Params{};

class WeightFunction:public WeightFunctionInterface
{
public:
    typedef DIPaCUS::Misc::DigitalBallIntersection DigitalBallIntersection;

    WeightFunction(double radius, const DigitalSet& ds):radius(radius)
    {
        DBI = new DigitalBallIntersection(radius,ds);
        intersectionSet = new DigitalSet(DBI->domain());
    }

    ~WeightFunction()
    {
        delete DBI;
        delete intersectionSet;
    }

    double operator()(const Point& p, bool sourceTarget)
    {
        if(sourceTarget) return pow( M_PI*pow(radius,2),2)*1000;
        else
        {
            intersectionSet->clear();
            DBI->operator()(*intersectionSet,p);
            return pow( DBI->digitalBall().size()/2.0 -(double) intersectionSet->size(),2);
        }
    }

    double radius;
    DigitalBallIntersection* DBI;
    DigitalSet* intersectionSet;
};

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    boost::filesystem::create_directories(id.outputFolder);

    DigitalSet _ds = Digital::resolveShape(id.shapeName,id.h);
    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));

    Neighborhood::Morphology morphologyNeighborhood(Neighborhood::Morphology::MorphologyElement::CIRCLE, id.neighborhoodSize);

    Timer T;
    T.start();
    for(int i=0;i<id.iterations;++i)
    {
        auto range = magLac::Core::addRange(morphologyNeighborhood.begin(),morphologyNeighborhood.end(),1);
        auto src = magLac::Core::Single::createCombinator(range);

        typedef decltype(src) MyCombinator;
        typedef MyCombinator::MyResolver MyResolver;

        typedef magLac::Core::MultiThread::ThreadInput<MyCombinator,UserVars,Params> MyThreadInput;
        typedef magLac::Core::MultiThread::Trigger<MyThreadInput> MyThreadTrigger;
        typedef magLac::Core::MultiThread::ThreadControl ThreadControl;


        MyThreadTrigger::CallbackFunction cbf = [&id,&ds,&morphologyNeighborhood](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
        {
            Neighborhood::Morphology::VectorOfCandidates c1(1);
            resolver >> c1;

            const Neighborhood::Morphology::Candidate& candidate = c1[0];

            FlowGraph* fg;
            DigitalSet candidateDS(ds.domain());
            morphologyNeighborhood.evaluateCandidate(candidateDS,candidate,ds);

            WeightFunction nwe(id.radius,candidateDS);
            fg = new FlowGraph(candidateDS,id.optBand,&nwe);


            double energyValue = Energy::elastica(fg->sourceNodes,id.radius,id.h,id.alpha);
            ti.vars.epVector.push_back(std::make_pair( fg,energyValue));

        };

        Params params;
        MyThreadTrigger mtTrigger(id.nThreads,1,cbf);

        mtTrigger.start(src,params);

        std::vector<UserVars::EvaluationPair> evaluationPairs;
        for(int i=0;i<id.nThreads;++i)
        {
            evaluationPairs.insert(evaluationPairs.end(),
                    mtTrigger.threadInputVector[i].vars.epVector.begin(),
                    mtTrigger.threadInputVector[i].vars.epVector.end());
        }

        std::sort(evaluationPairs.begin(),evaluationPairs.end(),[](const UserVars::EvaluationPair& ep1, const UserVars::EvaluationPair&  ep2){ return ep1.second < ep2.second;});

        const DigitalSet& bestDS = evaluationPairs[0].first->sourceNodes;
        Display::saveDigitalSetAsImage(bestDS,id.outputFolder+"/" + std::to_string(i) + ".pgm");

        ds.clear();
        ds.insert(bestDS.begin(),bestDS.end());

        for(auto ep:evaluationPairs)
        {
            delete ep.first;
        }


    }

    Display::saveDigitalSetAsImage(ds,id.outputFolder+"/final.pgm");


    T.end(std::cout);
    return 0;
}