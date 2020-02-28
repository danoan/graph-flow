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

        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Curve Curve;

        struct Candidate
        {
            enum OperationType{None,Inclusion,Removal};


            Candidate(){}
            Candidate(OperationType operationType,int length):
                    operationType(operationType),
                    length(length){};

            OperationType operationType;
            int length;
        };


        typedef std::vector<Candidate> VectorOfCandidates;
        typedef VectorOfCandidates::const_iterator CandidatesIterator;

    public:

        Random(int neighborhoodSize, int minLength, int maxLength)
        {
            std::random_device rd;
            std::default_random_engine re;
            std::uniform_int_distribution<int> udistLength(minLength,maxLength);

            candidates.resize(neighborhoodSize);
            for(int i=0;i<neighborhoodSize;++i)
            {
                candidates[i] = Candidate(Candidate::OperationType::Inclusion,udistLength(re));
            }

        }

        void evaluateCandidate(DigitalSet& dsOutput, const Candidate& candidate, const DigitalSet& dsInput) const
        {
            std::random_device rd;
            std::default_random_engine re;

            Curve curve;
            DIPaCUS::Misc::computeBoundaryCurve(curve,dsInput);

            const DGtal::Z2i::Domain& domain = dsInput.domain();
            DGtal::Z2i::KSpace kspace;
            kspace.init(domain.lowerBound(),domain.upperBound(),true);


            std::uniform_int_distribution<int> udistPos(0,curve.size());
            int pos = udistPos(re);

            auto itC = DGtal::Circulator<Curve::ConstIterator>(curve.begin(),curve.begin(),curve.end());

            dsOutput=dsInput;
            for(int i=0;i<pos;++i,++itC);
            for(int i=0;i<candidate.length;++i,++itC)
            {
                auto pixels = kspace.sUpperIncident(*itC);
                for(auto p:pixels)
                {
                    auto scoords = kspace.sCoords(p);
                    if(dsInput(scoords)) dsOutput.insert(scoords);
                }
            }

        }

        CandidatesIterator begin(){return candidates.begin();}
        CandidatesIterator end(){return candidates.end();}


    private:
        VectorOfCandidates candidates;
    };
}

#endif //GRAPH_FLOW_RANDOMNEIGHBORHOOD_H
