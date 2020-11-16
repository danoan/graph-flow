#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHFLOWITERATION
#define GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHFLOWITERATION

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::ShapeEvolution {
struct GraphFlowIteration {
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  enum IterationState { Init, Running, End };

  GraphFlowIteration(int iteration, double value, const DigitalSet &ds,
                     IterationState iterationState)
      : iteration(iteration),
        value(value),
        ds(ds),
        iterationState(iterationState) {}

  int iteration;
  double value;
  const DigitalSet &ds;
  IterationState iterationState;
};
}  // namespace GraphFlow::ShapeEvolution
#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHFLOWITERATION
