#ifndef GRAPH_FLOW_CORE_MORPHOLOGYNEIGHBORHOOD_H
#define GRAPH_FLOW_CORE_MORPHOLOGYNEIGHBORHOOD_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/digital.h>

namespace GraphFlow::Core::Neighborhood {
class Morphology {
 public:
  struct Blueprint {
    enum OperationType { None, Erosion, Dilation };

    Blueprint() = default;
    Blueprint(OperationType operationType, const int morphologySize)
        : operationType(operationType), morphologySize(morphologySize){};

    OperationType operationType;
    int morphologySize;
  };

  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DIPaCUS::Morphology::StructuringElement::Type MorphologyElement;
  typedef std::vector<Blueprint> VectorOfBlueprints;
  typedef VectorOfBlueprints::const_iterator BlueprintsIterator;

  Morphology(MorphologyElement me, int size) : me(me) {
    blueprints.resize(2 * size + 1);
    blueprints[0] = Blueprint(Blueprint::None, 0);
    for (int i = 1; i <= size; ++i) {
      blueprints[2 * (i - 1) + 1] = Blueprint(Blueprint::Erosion, i);
      blueprints[2 * i] = Blueprint(Blueprint::Dilation, i);
    }
  }

  BlueprintsIterator begin() const { return blueprints.begin(); }
  BlueprintsIterator end() const { return blueprints.end(); }

  void evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate,
                         const DigitalSet& dsInput) const;

 private:
  VectorOfBlueprints blueprints;
  MorphologyElement me;
};
}  // namespace GraphFlow::Core::Neighborhood

#endif  // GRAPH_FLOW_CORE_SHAPENEIGHBORHOOD_H
