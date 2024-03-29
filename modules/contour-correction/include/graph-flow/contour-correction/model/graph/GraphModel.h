#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHMODEL_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHMODEL_H

#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/utils/energy.h>

#include "graph-flow/contour-correction/model/Candidate.h"
#include "graph-flow/contour-correction/model/GraphSegInput.h"
#include "graph-flow/contour-correction/model/image/CVMatDistribution.h"
#include "graph-flow/contour-correction/model/image/DataDistribution.h"
#include "weight/Background.h"
#include "weight/BackgroundSeed.h"
#include "weight/Curvature.h"
#include "weight/Foreground.h"
#include "weight/ForegroundSeed.h"
#include "weight/Homogeneity.h"

namespace GraphFlow::ContourCorrection::Graph {

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef GraphFlow::Utils::Digital::Misc::DTL2 DTL2;

typedef GraphFlow::Core::TerminalWeight TerminalWeight;
typedef GraphFlow::Core::EdgeWeight EdgeWeight;

typedef std::vector<TerminalWeight*> TerminalWeightVector;
typedef std::vector<EdgeWeight*> EdgeWeightVector;

typedef GraphFlow::Core::FlowGraph FlowGraph;
typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

TerminalWeightVector prepareTerminalWeights(const GraphSegInput& gfi,
                                            const DigitalSet& ds,
                                            const DTL2& dtInterior,
                                            const DTL2& dtExterior);

EdgeWeightVector prepareEdgeWeightVector(const GraphSegInput& gfi,
                                         const DigitalSet& ds,
                                         const cv::Mat& colorImage);

double regionValue(double& fgv, double& bgv, const DigitalSet& ds,
                   const Image::CVMatDistribution& fgDistr,
                   const Image::CVMatDistribution& bgDistr);

double evaluateData(const GraphSegInput& gfi, const DigitalSet& ds);
double evaluateRegularization(const GraphSegInput& gfi, const DigitalSet& ds);
double evaluateRegularization(const GraphSegInput& gfi, const DigitalSet& ds,
                              const DigitalSet& belMask);

Domain getReducedDomain(const GraphSegInput& gfi,
                        const DigitalSet& candidateDS);

void buildLevelSet(DigitalSet& levelSet, const GraphSegInput& gfi,
                   const DigitalSet& candidateDS, DTL2& dtInterior,
                   DTL2& dtExterior);

DigitalSet* optimizeConnectedComponent(DigitalSet& vertexSet,
                                       const GraphSegInput& gfi,
                                       const DigitalSet& candidateDS);

template <class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(
    TNeighborhoodExplorer& neighExplorer);

}  // namespace GraphFlow::ContourCorrection::Graph

#include "GraphModel.hpp"

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHMODEL_H
