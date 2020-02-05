#include "graph-flow/core/FlowGraph.h"

namespace GraphFlow::Core
{
    FlowGraph::FlowGraph(const DigitalSet& ds,int optBand,WeightFunctionInterface* nwe,ArcPenalizationInterface* api):
    arcWeightMap(digraph),
    ntp(digraph),
    sourceNodes(ds.domain()),
    nwe(nwe),
    api(api)
    {
        using namespace DGtal::Z2i;
        using namespace GraphFlow::Utils;


        const Domain& domain = ds.domain();

        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);

        Digital::DTL2 interiorDT = Digital::interiorDistanceTransform(domain,ds);
        Digital::DTL2 exteriorDT = Digital::exteriorDistanceTransform(domain,ds);

        DigitalSet interiorPoints = Digital::level(interiorDT,optBand,0);
        DigitalSet exteriorPoints = Digital::level(exteriorDT,optBand,0);

        DigitalSet connectedToSource = Digital::level(interiorDT,optBand,optBand-1);
        DigitalSet connectedToTarget = Digital::level(exteriorDT,optBand,optBand-1);

        unsigned long int numNodes = interiorPoints.size()+exteriorPoints.size()+2;
        unsigned long int numArcs = connectedToSource.size()+connectedToTarget.size()+numNodes*4;

        digraph.reserveNode(numNodes+100);
        digraph.reserveArc(numArcs+100);

        for(auto p:interiorPoints) addNode(p);
        for(auto p:exteriorPoints) addNode(p);

        terminalSource = digraph.addNode();
        terminalTarget = digraph.addNode();

//        ArcWeightMap arcWeightMap(digraph);

        for(auto p:connectedToSource)
        {
            ListDigraph::Arc a = digraph.addArc( terminalSource,ptn[p] );
            arcWeightMap[a] = (*nwe)(p,true);
        }

        for(auto p:connectedToTarget)
        {
            ListDigraph::Arc a = digraph.addArc( ptn[p],terminalTarget );
            arcWeightMap[a] = (*nwe)(p,true);
        }


        DigitalSet allPoints(domain);
        allPoints.insert(interiorPoints.begin(),interiorPoints.end());
        allPoints.insert(exteriorPoints.begin(),exteriorPoints.end());

        connectNodes(arcWeightMap,ds,allPoints);


        for(auto it=api->begin();it!=api->end();++it)
        {
            if(it->arcType==ArcPenalizationElement::ArcType::Parallel)
            {
                ListDigraph::Arc a = digraph.addArc( ptn[it->source],ptn[it->target]);
                arcWeightMap[a] = it->value;
            }else if(it->arcType==ArcPenalizationElement::ArcType::Replace)
            {
                for(ListDigraph::OutArcIt arcIt( digraph,ptn[it->source] );arcIt!= lemon::INVALID;++arcIt)
                {
                    if(digraph.target(arcIt)==ptn[it->target])
                    {
                        arcWeightMap[arcIt] = it->value;
                        break;
                    }
                }
            }else if(it->arcType==ArcPenalizationElement::ArcType::FromSource)
            {
                ListDigraph::Arc a = digraph.addArc( terminalSource,ptn[it->target]);
                arcWeightMap[a] = it->value;
            }else if(it->arcType==ArcPenalizationElement::ArcType::ToTarget)
            {
                ListDigraph::Arc a = digraph.addArc( ptn[it->source],terminalTarget);
                arcWeightMap[a] = it->value;
            }
        }


        FlowComputer flow(digraph,arcWeightMap,terminalSource,terminalTarget);
        flow.run();

        cutValue = flow.flowValue();

        DIPaCUS::SetOperations::setDifference(sourceNodes,ds,allPoints);
        for(auto p:allPoints)
        {
            if( flow.minCut(ptn[p]) ) sourceNodes.insert(p);
        }

    }

    void FlowGraph::addNode(const Point& p)
    {
        ptn[p] = digraph.addNode();
        ntp[ ptn[p] ] = p;
    }

    void FlowGraph::connectNodes(ArcWeightMap& arcWeightMap, const DigitalSet& ds,const DigitalSet& allPoints)
    {
        Point neighbors[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        for(auto p:allPoints)
        {
            for(auto n:neighbors)
            {
                Point np = p+n;
                if( allPoints(np) )
                {
                    ListDigraph::Arc a = digraph.addArc( ptn[p],ptn[np] );
                    double w1 = (*nwe)(p,false);
                    double w2 = (*nwe)(np,false);

                    arcWeightMap[a] = (w1+w2)/2.0;
                }
            }
        }
    }
}