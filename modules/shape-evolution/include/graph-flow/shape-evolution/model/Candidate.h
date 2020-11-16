#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_CANDIDATE_H_
#define GRAPH_FLOW_SHAPE_EVOLUTION_CANDIDATE_H_

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::ShapeEvolution {
struct Candidate {
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  DigitalSet* ds;
  double value;
};
}  // namespace GraphFlow::ShapeEvolution

#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_CANDIDATE_H_
