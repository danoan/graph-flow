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

        setMax(vertexSet);

        for(int i=0;i<twv.size();++i)
        {
            for(auto p:vertexSet)
            {
                auto& tw = twv[i];
                double factor;
                if(tw->normalize()) factor=1.0/this->twvMax[i];
                else factor = 1.0;

                if(tw->type()==TerminalWeight::TerminalType::Source)
                {
                    ListDigraph::Arc a = digraph.addArc( terminalSource,ptn[p] );
                    double v = factor*tw->weight()*(*tw)(p);
                    arcWeightMap[a] = v;
                }
                else
                {
                    ListDigraph::Arc a = digraph.addArc( ptn[p],terminalTarget );
                    double v = factor*tw->weight()*(*tw)(p);
                    arcWeightMap[a] = v;
                }
            }
        }

        Point neighbors[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        for(int i=0;i<ewv.size();++i)
        {
            for(auto p:vertexSet)
            {
                for(auto n:neighbors)
                {
                    Point np = p+n;
                    if( vertexSet(np) )
                    {
                        ListDigraph::Arc a = digraph.addArc( ptn[p],ptn[np] );
    
                        auto& ew = ewv[i];
                        double factor;
                        if(ew->normalize()) factor=1.0/this->ewvMax[i];
                        else factor=1.0;
                        arcWeightMap[a] = factor*ew->weight()*(*ew)(p,np);
                    }
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

    void FlowGraph::setMax(const DigitalSet& vertexSet)
    {
        twvMax.resize(this->twv.size());

        int i=0;
        for(auto tw:twv)
        {
            double maxTerminalType= (*twv.begin())->operator()(*vertexSet.begin());

            for(auto p:vertexSet)
            {
                maxTerminalType = (*tw)(p)>maxTerminalType?(*tw)(p):maxTerminalType;
            }
            maxTerminalType=maxTerminalType==0?1:maxTerminalType;

            twvMax[i++] = maxTerminalType;
        }

        ewvMax.resize(this->ewv.size());
        Point neighbors[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        i=0;
        for(auto ew:ewv)
        {
            double maxEdgeType=0;
            for(auto p:vertexSet)
            {
                for(auto n:neighbors)
                {
                    Point np = p+n;
                    if( vertexSet(np) )
                    {
                         maxEdgeType = (*ew)(p,np)>maxEdgeType?(*ew)(p,np):maxEdgeType;
                    }
                }
            }
            maxEdgeType=maxEdgeType==0?1:maxEdgeType;
            ewvMax[i++]=maxEdgeType;
        }


    }


}