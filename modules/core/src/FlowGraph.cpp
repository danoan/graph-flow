#include "graph-flow/core/FlowGraph.h"

namespace GraphFlow::Core
{
    FlowGraph::FlowGraph(const DigitalSet& vertexSet,TerminalWeightVector twv, EdgeWeightVector ewv, HardConstraintVector hcv):
    arcWeightMap(digraph),
    ntp(digraph),
    sourceNodes(vertexSet.domain()),
    twv(twv),
    ewv(ewv),
    hcv(hcv)
    {
        using namespace DGtal::Z2i;
        using namespace GraphFlow::Utils;

        terminalSource = digraph.addNode();
        terminalTarget = digraph.addNode();
        for(auto p:vertexSet) addNode(p);


        for(auto p:vertexSet)
        {
            for(auto tw:twv)
            {
                if(tw->type()==TerminalWeight::TerminalType::Source)
                {
                    ListDigraph::Arc a = digraph.addArc( terminalSource,ptn[p] );
                    double v = (*tw)(p);
                    arcWeightMap[a] = v;
                }
                else
                {
                    ListDigraph::Arc a = digraph.addArc( ptn[p],terminalTarget );
                    double v = (*tw)(p);
                    arcWeightMap[a] = v;
                }
            }
        }

        Point neighbors[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        for(auto p:vertexSet)
        {
            for(auto n:neighbors)
            {
                Point np = p+n;
                if( vertexSet(np) )
                {
                    ListDigraph::Arc a = digraph.addArc( ptn[p],ptn[np] );
                    for(auto ew:ewv) arcWeightMap[a] = (*ew)(p,np);
                }
            }
        }

        for(auto hc:hcv)
        {
            for(auto it=hc->begin();it!=hc->end();++it)
            {
                if(it->arcType==HardConstraintElement::ArcType::Parallel)
                {
                    ListDigraph::Arc a = digraph.addArc( ptn[it->source],ptn[it->target]);
                    arcWeightMap[a] = it->value;
                }else if(it->arcType==HardConstraintElement::ArcType::Replace)
                {
                    for(ListDigraph::OutArcIt arcIt( digraph,ptn[it->source] );arcIt!= lemon::INVALID;++arcIt)
                    {
                        if(digraph.target(arcIt)==ptn[it->target])
                        {
                            arcWeightMap[arcIt] = it->value;
                            break;
                        }
                    }
                }else if(it->arcType==HardConstraintElement::ArcType::FromSource)
                {
                    ListDigraph::Arc a = digraph.addArc( terminalSource,ptn[it->target]);
                    arcWeightMap[a] = it->value;
                }else if(it->arcType==HardConstraintElement::ArcType::ToTarget)
                {
                    ListDigraph::Arc a = digraph.addArc( ptn[it->source],terminalTarget);
                    arcWeightMap[a] = it->value;
                }
            }
        }


        FlowComputer flow(digraph,arcWeightMap,terminalSource,terminalTarget);
        flow.run();

        cutValue = flow.flowValue();

        for(auto p:vertexSet)
        {
            if( flow.minCut(ptn[p]) ) sourceNodes.insert(p);
        }

    }

    void FlowGraph::addNode(const Point& p)
    {
        ptn[p] = digraph.addNode();
        ntp[ ptn[p] ] = p;
    }

}