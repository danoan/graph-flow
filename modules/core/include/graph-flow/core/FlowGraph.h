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
#include "WeightFunctionInterface.h"

namespace GraphFlow::Core
{
    class FlowGraph
    {
    private:
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        typedef lemon::ListDigraph ListDigraph;
        typedef ListDigraph::Node Node;
        typedef ListDigraph::ArcMap<double> ArcWeightMap;   //MinCut computation
        typedef lemon::Preflow <ListDigraph,ListDigraph::ArcMap<double> > FlowComputer;

        typedef std::map<DGtal::Z2i::Point,Node> PointToNode;

    public:
        typedef DGtal::Z2i::Point Point;
        typedef std::set<Point> PointSet;
        typedef std::function<double(const DigitalSet& ds,const Point& p,bool sourceTarget)> NodeWeightEvaluation;

    private:
        void connectNodes(ArcWeightMap& arcWeightMap, const DigitalSet& ds,const DigitalSet& allPoints);

    public:
        FlowGraph(const DigitalSet& ds,int optBand,WeightFunctionInterface* nwe);


    private:
        ListDigraph digraph;
        PointToNode ptn;
        WeightFunctionInterface* nwe;

    public:
        DigitalSet sourceNodes;
        double cutValue;
    };
}

#endif //GRAPH_FLOW_CORE_FLOWGRAPH_H
