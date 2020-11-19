#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHSEGITERATION_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHSEGITERATION_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::ImageSegmentation {
struct GraphSegIteration {
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  enum IterationState { Init, Running, End };

  GraphSegIteration(int iteration, double value, const DigitalSet& ds,
                    IterationState is)
      : iteration(iteration), value(value), ds(ds), iterationState(is) {}

  int iteration;
  double value;
  const DigitalSet& ds;
  IterationState iterationState;
};
}  // namespace GraphFlow::ImageSegmentation
#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHSEGITERATION_H
