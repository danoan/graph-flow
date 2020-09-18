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

void graphFlow(const GraphFlowInput& gfi, std::ostream& os, IterationCallback& icb);
}




#endif //GRAPH_FLOW_APP_GRAPH_FLOW_H

