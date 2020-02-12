#ifndef GRAPH_FLOW_GRAPH_SEG_H
#define GRAPH_FLOW_GRAPH_SEG_H

#include <DGtal/helpers/StdDefs.h>

#include <magLac/core/base/Range.hpp>

#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"
#include "model/StandardModel.h"

#include "control/NeighborhoodExplorer.h"

#include "utils.h"

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef std::function<void(const GraphSegIteration&)> IterationCallback;

struct UserVars
{
    typedef std::pair<DigitalSet*,double> EvaluationPair;
    
    void restart(){};
    std::vector<EvaluationPair> epVector;
};

struct Params{};

DigitalSet graphSeg(const GraphSegInput& gfi, std::ostream& os, IterationCallback& icb);


#endif //GRAPH_FLOW_GRAPH_SEG_H

