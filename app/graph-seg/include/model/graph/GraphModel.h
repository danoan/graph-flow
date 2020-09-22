#ifndef GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_GRAPH_GRAPHMODEL_H_
#define GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_GRAPH_GRAPHMODEL_H_

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>

#include "weight/ForegroundSeed.h"
#include "weight/BackgroundSeed.h"

#include "weight/Foreground.h"
#include "weight/Background.h"
#include "weight/Curvature.h"
#include "weight/Homogeneity.h"

#include "model/image/DataDistribution.h"
#include "model/image/CVMatDistribution.h"
#include "model/GraphSegInput.h"
#include "model/Candidate.h"
#include "input/InputData.h"

namespace App::Graph{

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef GraphFlow::Utils::Digital::DTL2 DTL2;

typedef GraphFlow::Core::TerminalWeight TerminalWeight;
typedef GraphFlow::Core::EdgeWeight EdgeWeight;

typedef std::vector<TerminalWeight*> TerminalWeightVector;
typedef std::vector<EdgeWeight*> EdgeWeightVector;

typedef GraphFlow::Core::FlowGraph FlowGraph;
typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const App::Image::DataDistribution& DD,const DigitalSet& ds);
EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage);

double regionValue(double& fgv, double& bgv,const DigitalSet& ds, const App::Image::CVMatDistribution& fgDistr, const App::Image::CVMatDistribution& bgDistr);
double evaluateData(const InputData& inputData,const DigitalSet& ds, const App::Image::DataDistribution& DD);

double diffDataValue(const DigitalSet& diffSet,const App::Image::DataDistribution& DD,bool fg);
DigitalSet* optimizeConnectedComponent(const DigitalSet& candidateDS, const App::GraphSegInput& gfi);



template<class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer& neighExplorer);

}

#include "GraphModel.hpp"

#endif //GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_GRAPH_GRAPHMODEL_H_