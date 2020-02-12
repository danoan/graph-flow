#ifndef GRAPH_FLOW_GRAPHSEGINPUT_H
#define GRAPH_FLOW_GRAPHSEGINPUT_H

#include <DGtal/helpers/StdDefs.h>
#include "input/InputData.h"
#include "model/DataDistribution.h"


struct GraphSegInput
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;

    GraphSegInput(const InputData& id, const DigitalSet& inputDS, const DataDistribution& dataDistribution):
    inputData(id),
    inputDS(inputDS),
    dataDistribution(dataDistribution)
    {}

    const InputData& inputData;
    const DigitalSet& inputDS;
    const DataDistribution& dataDistribution;
};

#endif //GRAPH_FLOW_GRAPHFLOWINPUT_H
