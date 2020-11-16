#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_UTILS_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_UTILS_H

#include <graph-flow/utils/string.h>
#include <graph-flow/shape-evolution/model/GraphFlowIteration.h>

namespace App::Utils {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef GraphFlow::ShapeEvolution::GraphFlowIteration GraphFlowIteration;

void writeEnergyData(const GraphFlowIteration &gfIteration, std::ostream &os);
}

#endif //GRAPH_FLOW_APP_GRAPH_FLOW_UTILS_H
