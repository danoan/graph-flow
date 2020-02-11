#ifndef GRAPH_FLOW_GRAPH_FLOW_H
#define GRAPH_FLOW_GRAPH_FLOW_H

#include <DGtal/helpers/StdDefs.h>

#include <magLac/core/base/Range.hpp>

#include "model/GraphFlowInput.h"
#include "model/GraphFlowIteration.h"
#include "model/StandardModel.h"

#include "control/NeighborhoodExplorer.h"

#include "utils.h"

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef std::function<void(const GraphFlowIteration&)> IterationCallback;

struct UserVars
{
    typedef std::pair<DigitalSet*,double> EvaluationPair;
    
    void restart(){};
    std::vector<EvaluationPair> epVector;
};

struct Params{};

void graphFlow(const GraphFlowInput& gfi, std::ostream& os, IterationCallback& icb);


#endif //GRAPH_FLOW_GRAPH_FLOW_H

