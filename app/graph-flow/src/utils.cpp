#include "utils.h"

namespace App::Utils {
void writeEnergyData(const GraphFlowIteration &gfIteration, std::ostream &os) {
  using namespace GraphFlow::Utils;
  int colLength = 20;

  os << String::fixedStrLength(colLength, gfIteration.iteration)
     << String::fixedStrLength(colLength, gfIteration.value) << "\n";
}

double evaluateEnergy(const InputData &id, const DigitalSet &ds) {
  using namespace GraphFlow::Utils;
  return Energy::elastica(ds, id.vradius, id.h, id.alpha, id.beta);
}

}