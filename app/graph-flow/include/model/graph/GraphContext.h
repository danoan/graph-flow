#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHCONTEXT_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHCONTEXT_H

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>

#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/utils/digital.h>

#include "weight/Foreground.h"
#include "weight/Background.h"
#include "weight/Curvature.h"

#include "model/GraphFlowInput.h"
#include "model/Candidate.h"
#include "utils.h"

namespace App::Graph {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;

typedef GraphFlow::Utils::Digital::DTL2 DTL2;

typedef GraphFlow::Core::TerminalWeight TerminalWeight;
typedef GraphFlow::Core::EdgeWeight EdgeWeight;

typedef std::vector<TerminalWeight *> TerminalWeightVector;
typedef std::vector<EdgeWeight *> EdgeWeightVector;

typedef GraphFlow::Core::FlowGraph FlowGraph;
typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

struct Context {
  typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

  Context(const GraphFlowInput &gfi, const DigitalSet &ds, const MorphologyNeighborhood &neighborhood) :
      gfi(gfi),
      ds(ds),
      neighborhood(neighborhood) {}

  const GraphFlowInput &gfi;
  const DigitalSet &ds;

  MorphologyNeighborhood neighborhood;
};

TerminalWeightVector prepareTerminalWeights(const InputData &id, const DTL2 &dtInterior, const DTL2 &dtExterior);
EdgeWeightVector prepareEdgeWeightVector(const InputData &id, const DigitalSet &ds);

template<class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer &neighExplorer);
}

#include "GraphContext.hpp"

#endif //GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHCONTEXT_H
