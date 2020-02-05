#ifndef GRAPH_FLOW_RANDOMNEIGHBORHOOD_H
#define GRAPH_FLOW_RANDOMNEIGHBORHOOD_H

#include <random>
#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/derivates/Misc.h>

#include <graph-flow/utils/digital.h>

namespace GraphFlow::Core::Neighborhood
{
    class Random
    {
    public:
        struct Candidate
        {
            enum OperationType{None,Erosion,Dilation};

            Candidate(){}
            Candidate(OperationType operationType):
                    operationType(operationType){};

            OperationType operationType;
        };

        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DIPaCUS::Misc::DigitalBallIntersection DigitalBallIntersection;

        typedef std::vector<Candidate> VectorOfCandidates;
        typedef VectorOfCandidates::const_iterator CandidatesIterator;

    public:

        Random(int ballRadius, int neighborhoodSize, int evaluationPoints):
        ballRadius(ballRadius),
        evaluationPoints(evaluationPoints)
        {
            std::default_random_engine re(rd());
            std::uniform_int_distribution<int> udist(0,1);

            candidates.resize(neighborhoodSize+1);
            candidates[0] = Candidate(Candidate::None);
            for(int i=1;i<=neighborhoodSize;++i)
            {
                Candidate::OperationType ot = otRange[ udist(re) ];

                candidates[i] = Candidate(ot);
            }
        }

        DigitalSet evaluateCandidate(const Candidate& candidate, const DigitalSet& dsInput)
        {
            DigitalSet dsOutput(dsInput.domain());
            evaluateCandidate(dsOutput,candidate,dsInput);

            return dsOutput;
        }

        void evaluateCandidate(DigitalSet& dsOutput, const Candidate& candidate, const DigitalSet& dsInput)
        {
            dsOutput=dsInput;
            if(candidate.operationType!=Candidate::None)
            {
                DigitalSet boundary(dsInput.domain());
                DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::EightNeighborhoodPredicate>(boundary,dsInput);
                DigitalBallIntersection DBI(ballRadius,dsInput);

                std::default_random_engine re(rd());
                std::uniform_int_distribution<int> udist(0,boundary.size()-1);
                std::vector<DGtal::Z2i::Point> boundaryPoints;
                boundaryPoints.insert(boundaryPoints.end(),boundary.begin(),boundary.end());


                DigitalSet intersectionSet(dsInput.domain());
                for(int i=0;i<evaluationPoints;++i)
                {
                    intersectionSet.clear();
                    DGtal::Z2i::Point p = boundaryPoints[ udist(re) ];
                    DBI.operator()(intersectionSet,p);

                    if(candidate.operationType==Candidate::Erosion)
                    {
                        for(auto pi:intersectionSet) dsOutput.erase(pi);
                    }else
                    {
                        for(auto pi:DBI.digitalBall()) if(!dsInput(pi+p)) dsOutput.insert(pi+p);
                    }
                }
            }
        }

        CandidatesIterator begin(){return candidates.begin();}
        CandidatesIterator end(){return candidates.end();}


    private:
        std::random_device rd;

        Candidate::OperationType otRange[2]={Candidate::OperationType::Erosion,Candidate::OperationType::Dilation};

        VectorOfCandidates candidates;

        int ballRadius;
        int evaluationPoints;
    };
}

#endif //GRAPH_FLOW_RANDOMNEIGHBORHOOD_H
