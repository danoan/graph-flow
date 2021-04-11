#include "graph-flow/contour-correction/model/graph/GraphModel.h"

namespace GraphFlow::ContourCorrection::Graph {

template <class TNeighborhoodExplorer>
typename TNeighborhoodExplorer::VisitNeighborFunction visitNeighbor(
    TNeighborhoodExplorer& neighExplorer) {
  typedef TNeighborhoodExplorer NE;
  typedef typename NE::MyThreadInfo MyThreadInfo;
  typedef typename NE::MyContext MyContext;

  return [](const MyContext& context, MyThreadInfo&& ti) mutable {
    typename MyContext::Neighborhood::VectorOfBlueprints c1(1);
    ti.resolver >> c1;

    typename MyContext::Neighborhood::Blueprint& blueprint = c1[0];
    const GraphSegInput& gfi = context.gfi;
    const DigitalSet& ds = context.ds;

    DigitalSet candidateDS(ds.domain());
    context.neighborhood.evaluateCandidate(candidateDS, blueprint, ds);

    if (candidateDS.empty()) return;

    DigitalSet belMask(candidateDS.domain());
    DigitalSet* optimalSet = optimizeConnectedComponent(belMask,gfi, candidateDS);
    if (optimalSet->empty()) {
      delete optimalSet;
      return;
    }

    double dataFidelityValue = evaluateData(gfi, ds);
    double elasticaValue = evaluateRegularization(gfi, *optimalSet,belMask);
    double energyValue = dataFidelityValue + elasticaValue;

    ti.data.mutableData.candidatesVector.push_back(
        Candidate{optimalSet, energyValue});
  };
}
}  // namespace GraphFlow::ContourCorrection::Graph