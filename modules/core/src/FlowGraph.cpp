#include "graph-flow/core/FlowGraph.h"

namespace GraphFlow::Core
{
    FlowGraph::FlowGraph(const DigitalSet& ds,int optBand,WeightFunctionInterface* nwe):sourceNodes(ds.domain()),nwe(nwe)
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

        digraph.reserveNode(numNodes);
        digraph.reserveArc(numArcs);

        for(auto p:interiorPoints) ptn[p] = digraph.addNode();
        for(auto p:exteriorPoints) ptn[p] = digraph.addNode();

        Node source = digraph.addNode();
        Node target = digraph.addNode();

        ArcWeightMap arcWeightMap(digraph);

        for(auto p:connectedToSource)
        {
            ListDigraph::Arc a = digraph.addArc( source,ptn[p] );
            arcWeightMap[a] = (*nwe)(p,true);
        }

        for(auto p:connectedToTarget)
        {
            ListDigraph::Arc a = digraph.addArc( ptn[p],target );
            arcWeightMap[a] = (*nwe)(p,true);
        }

        DigitalSet allPoints(domain);
        allPoints.insert(interiorPoints.begin(),interiorPoints.end());
        allPoints.insert(exteriorPoints.begin(),exteriorPoints.end());

        connectNodes(arcWeightMap,ds,allPoints);

        FlowComputer flow(digraph,arcWeightMap,source,target);
        flow.run();

        cutValue = flow.flowValue();

        DIPaCUS::SetOperations::setDifference(sourceNodes,ds,allPoints);
        for(auto p:allPoints)
        {
            if( flow.minCut(ptn[p]) ) sourceNodes.insert(p);
        }

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