#ifndef GRAPH_FLOW_CORE_RANDOMNEIGHBORHOOD_H
#define GRAPH_FLOW_CORE_RANDOMNEIGHBORHOOD_H

#include <random>

#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/derivates/Misc.h>

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/digital.h>

namespace GraphFlow::Core::Neighborhood
{
class Random
{
 public:
  struct Blueprint
  {
    enum OperationType{None,Erosion,Dilation,RandomOnContour,RandomOnDomain};

    Blueprint()=default;
    Blueprint(OperationType operationType,const int morphologySize):
        operationType(operationType),
        morphologySize(morphologySize){};

    OperationType operationType;
    int morphologySize;
  };

  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DIPaCUS::Morphology::StructuringElement::Type MorphologyElement;
  typedef std::vector<Blueprint> VectorOfBlueprints;
  typedef VectorOfBlueprints::const_iterator BlueprintsIterator;

  Random(MorphologyElement me, int size):me(me)
  {
    blueprints.resize(size+3);
    blueprints[0] = Blueprint(Blueprint::None,0);
    blueprints[1] = Blueprint(Blueprint::Erosion,1);
    blueprints[2] = Blueprint(Blueprint::Dilation,1);
    for(int i=0;i<size;++i)
    {
      blueprints[i+3] = Blueprint(Blueprint::RandomOnContour,0);
    }
  }

  BlueprintsIterator begin() const {return blueprints.begin();}
  BlueprintsIterator end() const {return blueprints.end();}

  void randomOnContour(DigitalSet& dsOutput) const;
  void randomOnDomain(DigitalSet& dsOutput) const;
  void evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate, const DigitalSet& dsInput) const;

 private:
  VectorOfBlueprints blueprints;
  MorphologyElement me;
};
}

#endif //GRAPH_FLOW_CORE_SHAPENEIGHBORHOOD_H
