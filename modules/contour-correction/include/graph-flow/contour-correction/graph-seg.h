#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_H

#include <DGtal/helpers/StdDefs.h>

#include <magLac/core/base/Range.hpp>

#include "control/NeighborhoodExplorer.h"
#include "model/Candidate.h"
#include "model/GraphSegInput.h"
#include "model/GraphSegIteration.h"
#include "model/graph/GraphContext.h"
#include "model/graph/GraphModel.h"
#include "utils.h"

namespace GraphFlow::ContourCorrection {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef std::function<void(const GraphSegIteration &)> IterationCallback;

struct UserVars {
  void restart(){};
  std::vector<Candidate> vectorOfCandidates;
};

struct Params {};

template <class TNeighExplorer>
double buildBestSolution(DigitalSet &solution, TNeighExplorer &neighExplorer);

template <class TNeighborhood>
DigitalSet graphSeg(const GraphSegInput &gfi, TNeighborhood &&neighborhood,
                    std::ostream &os, IterationCallback &icb);
}  // namespace GraphFlow::ContourCorrection

#include "graph-seg.hpp"

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_H
