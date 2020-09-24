#ifndef GRAPH_FLOW_APP_GRAPH_SEG_H
#define GRAPH_FLOW_APP_GRAPH_SEG_H

#include <DGtal/helpers/StdDefs.h>

#include <magLac/core/base/Range.hpp>

#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"
#include "model/graph/GraphContext.h"
#include "model/graph/GraphModel.h"
#include "model/Candidate.h"

#include "control/ComponentExplorer.h"

#include "utils/utils.h"

namespace App {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef std::function<void(const GraphSegIteration &)> IterationCallback;

struct UserVars {
  void restart() {};
  std::vector<Candidate> vectorOfCandidates;
};

struct Params {};

template<class TNeighExplorer>
void buildBestSolution(DigitalSet& solution, TNeighExplorer& neighExplorer);

DigitalSet graphSeg(const GraphSegInput &gfi, std::ostream &os, IterationCallback &icb);
}

#include "graph-seg.hpp"

#endif //GRAPH_FLOW_APP_GRAPH_SEG_H

