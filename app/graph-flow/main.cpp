#include <boost/filesystem.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Transform.h>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/single/Combinator.hpp"
#include "magLac/core/multithread/Trigger.h"
#include "magLac/core/multithread/ThreadInput.h"

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/Neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/core/WeightFunctionInterface.h>
#include <graph-flow/core/ArcPenalizationInterface.h>

#include <graph-flow/utils/digital.h>
#include <graph-flow/utils/display.h>
#include <graph-flow/utils/timer.h>
#include <graph-flow/utils/energy.h>
#include <graph-flow/utils/string.h>

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

class ArcPenalization:public ArcPenalizationInterface
{
public:
    typedef ArcPenalizationInterface::ArcPenalizationIterator ArcPenalizationIterator;

    ArcPenalization(double radius, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        using namespace DGtal::Z2i;
        double maxPenal = pow( M_PI*pow(radius,2),2)*1000;

        Point neighborhood[4] = {Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,ds);

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);
        for(auto c:curve)
        {
            auto pixels = kspace.sUpperIncident(c);
            Point pOut,pInn;
            for(auto _p:pixels)
            {
                Point originalCoords = kspace.sCoords(_p);
                if(ds(originalCoords)) pInn=originalCoords;
                else pOut = originalCoords;
            }

            if(pixelMask(pInn))
            {
                arcPenVector.push_back( ArcPenalizationElement( ArcPenalizationElement::FromSource, pInn,pInn,maxPenal) );
                arcPenVector.push_back( ArcPenalizationElement( ArcPenalizationElement::ToTarget, pOut,pOut,maxPenal) );
            }

        }
    }

    ArcPenalizationIterator begin(){ return arcPenVector.begin(); }
    ArcPenalizationIterator end(){ return arcPenVector.end(); }

private:
    std::vector<ArcPenalizationElement> arcPenVector;
};

struct EnergyIteration
{
    EnergyIteration(int iteration, double value) : iteration(iteration), value(value) {}

    int iteration;
    double value;
};

void writeEnergyData(std::vector<EnergyIteration>& eiVector,std::ofstream& ofs)
{
    int colLength=20;
    ofs << String::fixedStrLength(colLength,"#Iteration")
    << String::fixedStrLength(colLength,"Energy value") << "\n";

    for(auto ei:eiVector)
    {
        ofs << String::fixedStrLength(colLength,ei.iteration)
        << String::fixedStrLength(colLength,ei.value) << "\n";
    }
}

double evaluateEnergy(InputData& id, const DigitalSet& ds)
{
    if(id.energy==InputData::EnergyType::Elastica) return Energy::elastica(ds,id.radius,id.h,id.alpha);
    else if(id.energy==InputData::EnergyType::SElastica) return Energy::sElastica(ds,id.radius,id.h,id.alpha);
    else throw std::runtime_error("Unrecognized energy!");
}

DigitalSet getPixelMask(const std::string& pixelMaskFilepath, const Domain& domain, const Point& shift)
{
    DigitalSet _dsOutput(domain);
    DIPaCUS::Representation::imageAsDigitalSet(_dsOutput,pixelMaskFilepath,1);

    DigitalSet dsOutput(domain);
    for(auto p:_dsOutput) dsOutput.insert(p+shift);
    return dsOutput;
}

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    boost::filesystem::create_directories(id.outputFolder);

    DigitalSet _ds = Digital::resolveShape(id.shapeName,id.h);
    Point lb,ub;
    _ds.computeBoundingBox(lb,ub);
    Point border(20/id.h,20/id.h);

    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,border);
    Point shift = -lb+border;

    Neighborhood::Morphology morphologyNeighborhood(Neighborhood::Morphology::MorphologyElement::CIRCLE, id.neighborhoodSize);

    DigitalSet pixelMask = getPixelMask(id.pixelMaskFilepath,ds.domain(),shift);
    ArcPenalization api(id.radius,ds,pixelMask);

    std::vector<EnergyIteration> eiVector;
    Timer T;
    T.start();
    double lastEnergyValue= evaluateEnergy(id,ds);
    int i=0;
    while(true)
    {
        Display::saveDigitalSetAsImage(ds,id.outputFolder+"/" + String::nDigitsString(i,4) + ".pgm");
        eiVector.push_back( EnergyIteration(i,lastEnergyValue ) );

        if(i==id.iterations) break;

        auto range = magLac::Core::addRange(morphologyNeighborhood.begin(),morphologyNeighborhood.end(),1);
        auto src = magLac::Core::Single::createCombinator(range);

        typedef decltype(src) MyCombinator;
        typedef MyCombinator::MyResolver MyResolver;

        typedef magLac::Core::MultiThread::ThreadInput<MyCombinator,UserVars,Params> MyThreadInput;
        typedef magLac::Core::MultiThread::Trigger<MyThreadInput> MyThreadTrigger;
        typedef magLac::Core::MultiThread::ThreadControl ThreadControl;


        MyThreadTrigger::CallbackFunction cbf = [&id,&ds,&morphologyNeighborhood,&api](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
        {
            Neighborhood::Morphology::VectorOfCandidates c1(1);
            resolver >> c1;

            const Neighborhood::Morphology::Candidate& candidate = c1[0];

            FlowGraph* fg;
            DigitalSet candidateDS(ds.domain());
            morphologyNeighborhood.evaluateCandidate(candidateDS,candidate,ds);

            WeightFunction nwe(id.radius,candidateDS);
            fg = new FlowGraph(candidateDS,id.optBand,&nwe,&api);


            double energyValue = evaluateEnergy(id,fg->sourceNodes);
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
        ds.clear();
        ds.insert(bestDS.begin(),bestDS.end());

        for(auto ep:evaluationPairs)
        {
            delete ep.first;
        }


        if(id.iterations==-1)
            if( evaluationPairs[0].second > lastEnergyValue ) break;

        if( fabs(evaluationPairs[0].second-lastEnergyValue) < 1e-6 ) break;
        lastEnergyValue=evaluationPairs[0].second;
        ++i;

    }


    std::ofstream ofsInputData(id.outputFolder + "/inputData.txt");
    writeInputData(id,ofsInputData);
    ofsInputData.flush(); ofsInputData.close();

    std::ofstream ofsEnergy(id.outputFolder + "/energy.txt");
    writeEnergyData(eiVector,ofsEnergy);
    ofsEnergy << "#Execution time: ";
    T.end(ofsEnergy);
    ofsEnergy.flush(); ofsEnergy.close();

    return 0;
}