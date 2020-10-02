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
    enum OperationType{None,RandomOnContour,RandomOnDomain};

    Blueprint()=default;
    Blueprint(OperationType operationType):
        operationType(operationType){};

    OperationType operationType;
  };

  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef std::vector<Blueprint> VectorOfBlueprints;
  typedef VectorOfBlueprints::const_iterator BlueprintsIterator;

  Random(int size)
  {
    blueprints.resize(size+1);
    blueprints[0] = Blueprint(Blueprint::None);
    for(int i=0;i<size;++i)
    {
      blueprints[i+1] = Blueprint(Blueprint::RandomOnContour);
    }
  }

  BlueprintsIterator begin() const {return blueprints.begin();}
  BlueprintsIterator end() const {return blueprints.end();}

  void randomOnContour(DigitalSet& dsOutput) const;
  void randomOnDomain(DigitalSet& dsOutput) const;
  void evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate, const DigitalSet& dsInput) const;

 private:
  VectorOfBlueprints blueprints;
};
}

#endif //GRAPH_FLOW_CORE_SHAPENEIGHBORHOOD_H
