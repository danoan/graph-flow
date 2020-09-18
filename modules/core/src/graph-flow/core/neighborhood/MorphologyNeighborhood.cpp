#include "graph-flow/core/neighborhood/MorphologyNeighborhood.h"

namespace GraphFlow::Core::Neighborhood{

void Morphology::evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate, const DigitalSet& dsInput) const
{
  using namespace DIPaCUS::Morphology;
  if(candidate.operationType==Blueprint::OperationType::Erosion)
    erode(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
  else if(candidate.operationType==Blueprint::OperationType::Dilation)
    dilate(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
  else
    dsOutput = dsInput;
}

}