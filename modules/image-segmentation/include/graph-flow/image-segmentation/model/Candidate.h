#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_CANDIDATE_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_CANDIDATE_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::ImageSegmentation {
struct Candidate {
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  DigitalSet* ds;
  double value;
};
}  // namespace GraphFlow::ImageSegmentation

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_CANDIDATE_H
