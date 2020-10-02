#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_H

#include <DGtal/helpers/StdDefs.h>

#include <magLac/core/base/Range.hpp>

#include "model/Candidate.h"
#include "model/GraphFlowInput.h"
#include "model/GraphFlowIteration.h"
#include "model/graph/GraphContext.h"

#include "control/NeighborhoodExplorer.h"

#include "utils.h"

namespace App{
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef std::function<void(const GraphFlowIteration&)> IterationCallback;

struct UserVars
{
  void restart(){};
  std::vector<Candidate> candidatesVector;
};

struct Params{};

template<class TNeighExplorerIterator>
Candidate selectBestCandidate(TNeighExplorerIterator begin,TNeighExplorerIterator end);

template<class TNeighborhood>
void graphFlow(const GraphFlowInput &gfi, TNeighborhood&& neighborhood, std::ostream &os, IterationCallback &icb);
}

#include "graph-flow.hpp"




#endif //GRAPH_FLOW_APP_GRAPH_FLOW_H

