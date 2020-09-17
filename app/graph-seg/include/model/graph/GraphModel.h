#ifndef GRAPH_FLOW_STANDARDMODEL_H
#define GRAPH_FLOW_STANDARDMODEL_H

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>

#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/HardConstraint.h>
#include <graph-flow/utils/digital.h>

#include "constraint/ForegroundHard.h"
#include "constraint/BackgroundHard.h"

#include "weight/Foreground.h"
#include "weight/Background.h"
#include "weight/Curvature.h"
#include "weight/Homogeneity.h"

#include "model/GraphSegInput.h"
#include "model/DataDistribution.h"
#include "input/InputData.h"

#include "utils.h"

namespace Graph
{
    typedef GraphFlow::Utils::Digital::DTL2 DTL2;

    typedef GraphFlow::Core::TerminalWeight TerminalWeight;
    typedef GraphFlow::Core::EdgeWeight EdgeWeight;
    typedef GraphFlow::Core::HardConstraint HardConstraint;

    typedef std::vector<TerminalWeight*> TerminalWeightVector;
    typedef std::vector<EdgeWeight*> EdgeWeightVector;
    typedef std::vector<HardConstraint*> HardConstraintVector;

    typedef GraphFlow::Core::FlowGraph FlowGraph;
    typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds);
    TerminalWeightVector prepareTerminalWeights(const InputData& id, const DTL2& dtInterior, const DTL2& dtExterior,const DataDistribution& DD,const DigitalSet& ds);
    EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds, const cv::Mat& colorImage);

    
    double regionValue(double& fgv, double& bgv,const DigitalSet& ds, const CVMatDistribution& fgDistr, const CVMatDistribution& bgDistr);
    double evaluateData(const InputData& inputData,const DigitalSet& ds, const DataDistribution& DD);

    template<class TNeighborhoodExplorer>
    typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer& neighExplorer);
}

#include "GraphModel.hpp"

#endif //GRAPH_FLOW_STANDARDMODEL_H
