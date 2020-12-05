#include "GraphContext.h"

namespace GraphFlow::ShapeEvolution::Graph {
template <class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(
    TNeighborhoodExplorer &neighExplorer) {
  typedef TNeighborhoodExplorer NE;
  typedef typename NE::MyResolver MyResolver;
  typedef typename NE::MyThreadInput MyThreadInput;
  typedef typename NE::ThreadControl ThreadControl;
  typedef typename NE::Context MyContext;
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DGtal::Z2i::Point Point;

  return [](const MyContext &context, MyResolver &resolver, MyThreadInput &ti,
            ThreadControl &tc) {
    typename MyContext::Neighborhood::VectorOfBlueprints c1(1);
    resolver >> c1;

    const typename MyContext::Neighborhood::Blueprint &blueprint = c1[0];

    DigitalSet candidateDS(context.ds.domain());
    context.neighborhood.evaluateCandidate(candidateDS, blueprint, context.ds);

    Point lb, ub;
    candidateDS.computeBoundingBox(lb, ub);
    Point optBandBorder(context.gfi.optBand + 1, context.gfi.optBand + 1);
    Domain reducedDomain(lb - optBandBorder, ub + optBandBorder);

    auto dtInterior = GraphFlow::Utils::Digital::interiorDistanceTransform(
        reducedDomain, candidateDS);
    auto dtExterior = GraphFlow::Utils::Digital::exteriorDistanceTransform(
        reducedDomain, candidateDS);

    auto ewv = prepareEdgeWeightVector(context.gfi, candidateDS);
    auto twv = prepareTerminalWeights(context.gfi, dtInterior, dtExterior);

    DigitalSet vertexSet =
        GraphFlow::Utils::Digital::level(dtInterior, context.gfi.optBand, 0);
    vertexSet +=
        GraphFlow::Utils::Digital::level(dtExterior, context.gfi.optBand, 0);

    FlowGraph fg(vertexSet, twv, ewv);
    DigitalSet *solutionSet = new DigitalSet(candidateDS.domain());
    DIPaCUS::SetOperations::setDifference(*solutionSet, candidateDS, vertexSet);
    solutionSet->insert(fg.sourceNodes.begin(), fg.sourceNodes.end());

    double energyValue = GraphFlow::Utils::Energy::elastica(
        *solutionSet, context.gfi.vradius, context.gfi.h, context.gfi.alpha,
        context.gfi.beta);
    ti.vars.candidatesVector.push_back(
        ShapeEvolution::Candidate{solutionSet, energyValue});

    for (auto ew : ewv) delete ew;
    for (auto tw : twv) delete tw;
  };
}
}  // namespace GraphFlow::ShapeEvolution::Graph