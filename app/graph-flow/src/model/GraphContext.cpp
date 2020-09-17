#include "model/graph/GraphContext.h"

namespace App::Graph {
TerminalWeightVector prepareTerminalWeights(const InputData &id, const DTL2 &dtInterior, const DTL2 &dtExterior) {
  TerminalWeightVector twv(2);
  twv[0] = new Weight::Foreground(dtInterior, id.optBand, id.radius);
  twv[1] = new Weight::Background(dtExterior, id.optBand, id.radius);

  return twv;
}

EdgeWeightVector prepareEdgeWeightVector(const InputData &id, const DigitalSet &ds) {
  EdgeWeightVector ewv(1);
  ewv[0] = new Weight::Curvature(id.radius, id.h, ds);

  return ewv;
}
}