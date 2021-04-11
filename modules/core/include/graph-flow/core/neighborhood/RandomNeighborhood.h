#ifndef GRAPH_FLOW_CORE_RANDOMNEIGHBORHOOD_H
#define GRAPH_FLOW_CORE_RANDOMNEIGHBORHOOD_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/digital/morphology.h>
#include <graph-flow/utils/digital/shapes.h>

#include <random>

namespace GraphFlow::Core::Neighborhood {
class Random {
 public:
  struct Blueprint {
    enum OperationType {
      None,
      RandomOnContour,
      Dilation,
      Erosion
    };

    Blueprint() = default;
    Blueprint(OperationType operationType) : operationType(operationType){};

    OperationType operationType;
  };

  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef std::vector<Blueprint> VectorOfBlueprints;
  typedef VectorOfBlueprints::const_iterator BlueprintsIterator;

  Random(int size) {
    blueprints.resize(size + 3);
    blueprints[0] = Blueprint(Blueprint::None);
    blueprints[1] = Blueprint(Blueprint::Dilation);
    blueprints[2] = Blueprint(Blueprint::Erosion);
    for (int i = 0; i < size; ++i) {
      blueprints[i + 3] = Blueprint(Blueprint::RandomOnContour);
    }
  }

  BlueprintsIterator begin() const { return blueprints.begin(); }
  BlueprintsIterator end() const { return blueprints.end(); }

  void randomOnContour(DigitalSet& dsOutput) const;
  void evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate,
                         const DigitalSet& dsInput) const;

 private:
  VectorOfBlueprints blueprints;
};
}  // namespace GraphFlow::Core::Neighborhood

#endif  // GRAPH_FLOW_CORE_SHAPENEIGHBORHOOD_H
