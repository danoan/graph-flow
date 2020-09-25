#ifndef GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_GRAPH_GRAPHMODEL_H_
#define GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_GRAPH_GRAPHMODEL_H_

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/neighborhood/RandomNeighborhood.h>

#include "weight/ForegroundSeed.h"
#include "weight/BackgroundSeed.h"
#include "weight/ForegroundChanVese.h"
#include "weight/BackgroundChanVese.h"
#include "weight/Curvature.h"


#include "model/GraphSegInput.h"
#include "model/Candidate.h"
#include "input/InputData.h"

#include "utils/utils.h"
#include "utils/data-term.h"

namespace App::Graph{

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef GraphFlow::Utils::Digital::DTL2 DTL2;

typedef GraphFlow::Core::TerminalWeight TerminalWeight;
typedef GraphFlow::Core::EdgeWeight EdgeWeight;

typedef std::vector<TerminalWeight*> TerminalWeightVector;
typedef std::vector<EdgeWeight*> EdgeWeightVector;

typedef GraphFlow::Core::FlowGraph FlowGraph;
typedef GraphFlow::Core::Neighborhood::Random RandomNeighborhood;

TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const cv::Mat& cvImgIn,const DigitalSet& ds, const cv::Vec3d& avgF, const cv::Vec3d& avgB);
EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage);


double evaluateData(const InputData& inputData,const DigitalSet& ds, const cv::Mat& cvImgIn);
void optimizeConnectedComponent(DigitalSet& solutionSet,const DigitalSet& candidateDS, const App::GraphSegInput& gfi, const cv::Vec3d& avgF, const cv::Vec3d& avgB);



template<class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer& neighExplorer);

}

#include "GraphModel.hpp"

#endif //GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_GRAPH_GRAPHMODEL_H_
