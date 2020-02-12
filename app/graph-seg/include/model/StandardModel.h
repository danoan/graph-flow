#ifndef GRAPH_FLOW_STANDARDMODEL_H
#define GRAPH_FLOW_STANDARDMODEL_H

#include <graph-flow/core/FlowGraph.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>

#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/HardConstraint.h>
#include <graph-flow/utils/digital.h>

#include "weight/Foreground.h"
#include "weight/Background.h"
#include "weight/Curvature.h"

#include "constraint/FixedPixels.h"

#include "model/GraphSegInput.h"
#include "model/DataDistribution.h"
#include "input/InputData.h"

#include "utils.h"

namespace StandardModel
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

    HardConstraintVector prepareHardConstraints(const InputData& id, const DigitalSet& ds, const DigitalSet& pixelMask);
    TerminalWeightVector prepareTerminalWeights(const DataDistribution& DD,double dataTermWeight);
    EdgeWeightVector prepareEdgeWeightVector(const InputData& id, const DigitalSet& ds);

    struct Context
    {
        typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

        Context(const GraphSegInput& gfi, const DigitalSet& ds, const HardConstraintVector& hcv, const TerminalWeightVector& twv, const MorphologyNeighborhood& neighborhood):
                gfi(gfi),
                ds(ds),
                neighborhood(neighborhood),
                hcv(hcv),twv(twv){}

        const GraphSegInput& gfi;
        const DigitalSet& ds;

        MorphologyNeighborhood neighborhood;
        const HardConstraintVector& hcv;
        const TerminalWeightVector& twv;
    };


    double evaluateData(const InputData& inputData,const DigitalSet& ds, const DataDistribution& DD);

    template<class TNeighborhoodExplorer>
    typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer& neighExplorer);
}

#include "StandardModel.hpp"

#endif //GRAPH_FLOW_STANDARDMODEL_H
