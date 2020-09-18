#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHFLOWINPUT_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHFLOWINPUT_H

#include "input/InputData.h"
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/EdgeWeight.h>

namespace App{
struct GraphFlowInput {
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  GraphFlowInput(const InputData &inputData, DigitalSet &inputDS)
      : inputData(inputData), inputDS(inputDS){}

  const InputData &inputData;

  const DigitalSet &inputDS;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_FLOW_GRAPHFLOWINPUT_H
