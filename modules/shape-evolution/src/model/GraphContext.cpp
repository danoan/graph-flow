#include "graph-flow/shape-evolution/model/graph/GraphContext.h"

namespace GraphFlow::ShapeEvolution::Graph {
TerminalWeightVector prepareTerminalWeights(const GraphFlowInput &gfi,
                                            const DTL2 &dtInterior,
                                            const DTL2 &dtExterior) {
  TerminalWeightVector twv(2);
  twv[0] = new Weight::Foreground(dtInterior, gfi.optBand, gfi.radius);
  twv[1] = new Weight::Background(dtExterior, gfi.optBand, gfi.radius);

  return twv;
}

EdgeWeightVector prepareEdgeWeightVector(const GraphFlowInput &gfi,
                                         const DigitalSet &ds) {
  EdgeWeightVector ewv(1);
  ewv[0] = new Weight::Curvature(gfi.radius, gfi.h, ds);

  return ewv;
}
}  // namespace GraphFLow::ShapeEvolution::Graph