#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHFLOWITERATION
#define GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHFLOWITERATION

#include <DGtal/helpers/StdDefs.h>

namespace App {
struct GraphFlowIteration {
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  enum IterationState { Init, Running, End };

  GraphFlowIteration(int iteration, double value, const DigitalSet &ds, IterationState iterationState) :
      iteration(iteration),
      value(value),
      ds(ds),
      iterationState(iterationState) {}

  int iteration;
  double value;
  const DigitalSet &ds;
  IterationState iterationState;
};
}
#endif //GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHFLOWITERATION

