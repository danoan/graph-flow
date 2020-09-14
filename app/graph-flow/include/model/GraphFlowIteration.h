#ifndef GRAPHFLOWITERATION
#define GRAPHFLOWITERATION

#include <DGtal/helpers/StdDefs.h>

struct GraphFlowIteration
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    enum IterationState{Init,Running,End};

    GraphFlowIteration(int iteration, double value, const DigitalSet& ds, IterationState iterationState) :
    iteration(iteration),
    value(value),
    ds(ds),
    iterationState(iterationState) {}

    int iteration;
    double value;
    const DigitalSet& ds;
    IterationState iterationState;
};
#endif //GRAPHFLOWITERATION
