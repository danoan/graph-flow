#ifndef GRAPH_FLOW_CORE_FLOWGRAPH_H
#define GRAPH_FLOW_CORE_FLOWGRAPH_H

#include <map>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/SetOperations.h>

#include <lemon/list_graph.h>
#include <lemon/graph_to_eps.h>

#include <lemon/preflow.h>
#include <lemon/adaptors.h>

#include <graph-flow/utils/digital.h>
#include <graph-flow/utils/timer.h>

#include "EdgeWeight.h"
#include "HardConstraint.h"
#include "TerminalWeight.h"

namespace GraphFlow::Core
{
    class FlowGraph
    {
    public:
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Point Point;

        typedef lemon::ListDigraph ListDigraph;
        typedef ListDigraph::Node Node;
        typedef ListDigraph::ArcMap<double> ArcWeightMap;   //MinCut computation
        typedef lemon::Preflow <ListDigraph,ListDigraph::ArcMap<double> > FlowComputer;

        typedef std::map<DGtal::Z2i::Point,Node> PointToNode;
        typedef ListDigraph::NodeMap<DGtal::Z2i::Point> NodeToPoint;

        typedef std::vector<TerminalWeight*> TerminalWeightVector;
        typedef std::vector<HardConstraint*> HardConstraintVector;
        typedef std::vector<EdgeWeight*> EdgeWeightVector;


    private:
        void addNode(const Point& p);
        void setMax(const DigitalSet& vertexSet);

    public:
        FlowGraph(const DigitalSet& vertexSet,TerminalWeightVector twv, EdgeWeightVector ewv, HardConstraintVector hcv);


    public:
        ListDigraph digraph;
        ArcWeightMap arcWeightMap;

        ListDigraph::Node terminalSource;
        ListDigraph::Node terminalTarget;

        PointToNode ptn;
        NodeToPoint ntp;

        TerminalWeightVector twv;
        EdgeWeightVector ewv;
        HardConstraintVector hcv;

    public:
        DigitalSet sourceNodes;
        double cutValue;

        std::vector<double> twvMax;
        std::vector<double> ewvMax;
    };
}

#endif //GRAPH_FLOW_CORE_FLOWGRAPH_H
