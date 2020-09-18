#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_UTILS_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_UTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/utils/string.h>
#include <graph-flow/utils/energy.h>

#include "input/InputData.h"
#include "model/GraphFlowIteration.h"

namespace App::Utils {
typedef DGtal::Z2i::DigitalSet DigitalSet;

void writeEnergyData(const GraphFlowIteration &gfIteration, std::ostream &os);
double evaluateEnergy(const InputData &id, const DigitalSet &ds);
}

#endif //GRAPH_FLOW_APP_GRAPH_FLOW_UTILS_H
