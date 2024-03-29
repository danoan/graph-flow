#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_SHAPE_EVOLUTION_H
#define GRAPH_FLOW_SHAPE_EVOLUTION_SHAPE_EVOLUTION_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/energy.h>

#include <magLac/core/base/Range.hpp>

#include "control/NeighborhoodExplorer.h"
#include "model/Candidate.h"
#include "model/GraphFlowInput.h"
#include "model/GraphFlowIteration.h"
#include "model/graph/GraphContext.h"

namespace GraphFlow::ShapeEvolution {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef std::function<void(const GraphFlowIteration &)> IterationCallback;

struct MyThreadData{
  struct MutableData {
    void restart(){};
    std::vector<Candidate> candidatesVector;
  };

  struct ConstantData {};

  MutableData mutableData;
  ConstantData constantData;
};

template <class TNeighExplorerIterator>
Candidate selectBestCandidate(TNeighExplorerIterator begin,
                              TNeighExplorerIterator end);

template <class TNeighborhood>
void graphFlow(const GraphFlowInput &gfi, TNeighborhood &&neighborhood,
               std::ostream &os, IterationCallback &icb);
}  // namespace GraphFlow::ShapeEvolution

#include "shape-evolution.hpp"

#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_SHAPE_EVOLUTION_H
