#include "StandardModel.h"

namespace StandardModel
{
template<class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer& neighExplorer)
{
  typedef TNeighborhoodExplorer NE;
  typedef typename NE::MyResolver MyResolver;
  typedef typename NE::MyThreadInput MyThreadInput;
  typedef typename NE::ThreadControl ThreadControl;
  typedef typename NE::Context MyContext;

  return
      [](const MyContext& context, MyResolver& resolver, MyThreadInput & ti, ThreadControl& tc)
      {
        MorphologyNeighborhood::VectorOfCandidates c1(1);
        resolver >> c1;

        const MorphologyNeighborhood::Candidate& candidate = c1[0];


        DigitalSet candidateDS(context.ds.domain());
        context.neighborhood.evaluateCandidate(candidateDS,candidate,context.ds);
        if(candidateDS.empty()) return;


        //Include fg seeds in the current candidate
        for(auto pt:context.gfi.dataDistribution.fgSeeds) candidateDS.insert(pt);


        Point lb,ub;
        candidateDS.computeBoundingBox(lb,ub);
        Point optBandBorder(context.gfi.inputData.optBand+1,context.gfi.inputData.optBand+1);
        Domain reducedDomain(lb-2*optBandBorder,ub+2*optBandBorder);

        auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(reducedDomain,candidateDS);
        auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(reducedDomain,candidateDS);

        auto ewv = prepareEdgeWeightVector(context.gfi.inputData,candidateDS,context.gfi.dataDistribution.segResultImg);
        auto twv = prepareTerminalWeights(context.gfi.inputData,dtInterior,dtExterior,context.gfi.dataDistribution,context.ds);

        DigitalSet _vertexSet = GraphFlow::Utils::Digital::level(dtInterior,context.gfi.inputData.optBand,0);
        _vertexSet += GraphFlow::Utils::Digital::level(dtExterior,context.gfi.inputData.optBand,0);
        DigitalSet vertexSet(context.ds.domain());
        for(auto p:_vertexSet) if(context.ds.domain().isInside(p)) vertexSet.insert(p);


        FlowGraph fg(vertexSet,twv,ewv,context.hcv);
        DigitalSet* solutionSet = new DigitalSet(candidateDS.domain());
        DIPaCUS::SetOperations::setDifference(*solutionSet,candidateDS,vertexSet);

        for(auto p:fg.sourceNodes)
        {
          if(context.ds.domain().isInside(p)) solutionSet->insert(p);
        }

        double fgv;
        double bgv;

        double dataFidelityValue= evaluateData(fgv,bgv,context.gfi.inputData,*solutionSet,context.gfi.dataDistribution);

        double dAlpha;
        if( (bgv-fgv)>0 ) dAlpha=0.0;
        else dAlpha=1.0;

//            std::cout << dAlpha << ", ";

        double elasticaValue = evaluateEnergy(context.gfi.inputData,*solutionSet,dAlpha);


        double energyValue = dataFidelityValue + elasticaValue;



        ti.vars.epVector.push_back(std::make_pair( solutionSet,energyValue));

        for(auto ew:ewv) delete ew;
        for(auto tw:twv) delete tw;
      };
}
}