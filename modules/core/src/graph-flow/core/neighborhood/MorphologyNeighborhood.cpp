#include "graph-flow/core/neighborhood/MorphologyNeighborhood.h"

namespace GraphFlow::Core::Neighborhood{

void Morphology::evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate, const DigitalSet& dsInput) const
{
  using namespace DGtal::Z2i;
  typedef DIPaCUS::Morphology::StructuringElement StructuringElement;

  if(candidate.operationType==Blueprint::None){
    dsOutput = dsInput;
  }else if(candidate.operationType==Blueprint::Dilation){
    dilate(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
  }else if(candidate.operationType==Blueprint::Erosion){
    erode(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
  }
}

}
