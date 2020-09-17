#include "GraphContext.h"

namespace App::Graph {
template<class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(TNeighborhoodExplorer &neighExplorer) {
  typedef TNeighborhoodExplorer NE;
  typedef typename NE::MyResolver MyResolver;
  typedef typename NE::MyThreadInput MyThreadInput;
  typedef typename NE::ThreadControl ThreadControl;
  typedef typename NE::Context MyContext;

  return
      [](const MyContext &context, MyResolver &resolver, MyThreadInput &ti, ThreadControl &tc) {
        MorphologyNeighborhood::VectorOfCandidates c1(1);
        resolver >> c1;

        const MorphologyNeighborhood::Candidate &candidate = c1[0];

        DigitalSet candidateDS(context.ds.domain());
        context.neighborhood.evaluateCandidate(candidateDS, candidate, context.ds);

        Point lb, ub;
        candidateDS.computeBoundingBox(lb, ub);
        Point optBandBorder(context.gfi.inputData.optBand + 1, context.gfi.inputData.optBand + 1);
        Domain reducedDomain(lb - optBandBorder, ub + optBandBorder);

        auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(reducedDomain, candidateDS);
        auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(reducedDomain, candidateDS);

        auto ewv = prepareEdgeWeightVector(context.gfi.inputData, candidateDS);
        auto twv = prepareTerminalWeights(context.gfi.inputData, dtInterior, dtExterior);

        DigitalSet vertexSet = GraphFlow::Utils::Digital::level(dtInterior, context.gfi.inputData.optBand, 0);
        vertexSet += GraphFlow::Utils::Digital::level(dtExterior, context.gfi.inputData.optBand, 0);


        FlowGraph fg(vertexSet, twv, ewv);
        DigitalSet *solutionSet = new DigitalSet(candidateDS.domain());
        DIPaCUS::SetOperations::setDifference(*solutionSet, candidateDS, vertexSet);
        solutionSet->insert(fg.sourceNodes.begin(), fg.sourceNodes.end());

        double energyValue = App::Utils::evaluateEnergy(context.gfi.inputData, *solutionSet);
        ti.vars.candidatesVector.push_back( App::Candidate{solutionSet, energyValue} );

        for (auto ew:ewv) delete ew;
        for (auto tw:twv) delete tw;
      };
}
}