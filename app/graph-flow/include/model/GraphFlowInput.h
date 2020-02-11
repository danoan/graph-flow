#ifndef GRAPH_FLOW_GRAPHFLOWINPUT_H
#define GRAPH_FLOW_GRAPHFLOWINPUT_H

#include "input/InputData.h"
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/core/HardConstraint.h>
#include <graph-flow/core/EdgeWeight.h>

struct GraphFlowInput
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;

    GraphFlowInput(const InputData &inputData, DigitalSet &inputDS, DigitalSet &pixelMask) : inputData(inputData), inputDS(inputDS), pixelMask(pixelMask){}

    const InputData& inputData;

    const DigitalSet& inputDS;
    const DigitalSet& pixelMask;
};

#endif //GRAPH_FLOW_GRAPHFLOWINPUT_H
