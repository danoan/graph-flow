#ifndef GRAPH_FLOW_CORE_MORPHOLOGYNEIGHBORHOOD_H
#define GRAPH_FLOW_CORE_MORPHOLOGYNEIGHBORHOOD_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/digital.h>

namespace GraphFlow::Core::Neighborhood
{
    class Morphology
    {
    public:
        struct Candidate
        {
            enum OperationType{None,Erosion,Dilation};


            Candidate(){}
            Candidate(OperationType operationType,const int morphologySize):
            operationType(operationType),
            morphologySize(morphologySize){};

            OperationType operationType;
            int morphologySize;
        };

        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DIPaCUS::Morphology::StructuringElement::Type MorphologyElement;
        typedef std::vector<Candidate> VectorOfCandidates;
        typedef VectorOfCandidates::const_iterator CandidatesIterator;

        Morphology(MorphologyElement me, int size):me(me)
        {
            candidates.resize(2*size+1);
            candidates[0] = Candidate(Candidate::None,0);
            for(int i=1;i<=size;++i)
            {
                candidates[2*(i-1)+1] = Candidate(Candidate::Erosion,i);
                candidates[2*i] = Candidate(Candidate::Dilation,i);
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
            using namespace DIPaCUS::Morphology;
            if(candidate.operationType==Candidate::OperationType::Erosion)
                erode(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
            else if(candidate.operationType==Candidate::OperationType::Dilation)
                dilate(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
            else
                dsOutput = dsInput;
        }

        CandidatesIterator begin(){return candidates.begin();}
        CandidatesIterator end(){return candidates.end();}


    private:
        VectorOfCandidates candidates;
        MorphologyElement me;
    };
}

#endif //GRAPH_FLOW_CORE_SHAPENEIGHBORHOOD_H
