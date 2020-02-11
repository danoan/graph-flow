#ifndef GRAPHFLOWITERATION
#define GRAPHFLOWITERATION

#include <DGtal/helpers/StdDefs.h>

struct GraphFlowIteration
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;

    GraphFlowIteration(int iteration, double value, const DigitalSet& ds) :
    iteration(iteration),
    value(value),
    ds(ds) {}

    int iteration;
    double value;
    const DigitalSet& ds;
};
#endif //GRAPHFLOWITERATION
