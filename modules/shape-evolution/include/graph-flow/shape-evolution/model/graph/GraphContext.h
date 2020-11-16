#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHCONTEXT_H
#define GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHCONTEXT_H

#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/utils/digital.h>
#include <graph-flow/utils/energy.h>

#include "graph-flow/shape-evolution/model/Candidate.h"
#include "graph-flow/shape-evolution/model/GraphFlowInput.h"
#include "weight/Background.h"
#include "weight/Curvature.h"
#include "weight/Foreground.h"

namespace GraphFlow::ShapeEvolution::Graph {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;

typedef GraphFlow::Utils::Digital::DTL2 DTL2;

typedef GraphFlow::Core::TerminalWeight TerminalWeight;
typedef GraphFlow::Core::EdgeWeight EdgeWeight;

typedef std::vector<TerminalWeight *> TerminalWeightVector;
typedef std::vector<EdgeWeight *> EdgeWeightVector;

typedef GraphFlow::Core::FlowGraph FlowGraph;

template <class TNeighborhood>
struct Context {
  typedef TNeighborhood Neighborhood;

  Context(const GraphFlowInput &gfi, const DigitalSet &ds,
          const Neighborhood &neighborhood)
      : gfi(gfi), ds(ds), neighborhood(neighborhood) {}

  const GraphFlowInput &gfi;
  const DigitalSet &ds;

  Neighborhood neighborhood;
};

TerminalWeightVector prepareTerminalWeights(const GraphFlowInput &gfi,
                                            const DTL2 &dtInterior,
                                            const DTL2 &dtExterior);
EdgeWeightVector prepareEdgeWeightVector(const GraphFlowInput &gfi,
                                         const DigitalSet &ds);

template <class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(
    TNeighborhoodExplorer &neighExplorer);
}  // namespace GraphFlow::ShapeEvolution::Graph

#include "GraphContext.hpp"

#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHCONTEXT_H
