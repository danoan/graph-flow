#ifndef GRAPHSEGITERATION
#define GRAPHSEGITERATION

#include <DGtal/helpers/StdDefs.h>

struct GraphSegIteration
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    enum IterationState{Init,Running,End};

    GraphSegIteration(int iteration, double value, const DigitalSet& ds,IterationState is) :
    iteration(iteration),
    value(value),
    ds(ds),
    iterationState(is) {}

    int iteration;
    double value;
    const DigitalSet& ds;
    IterationState iterationState;
};
#endif //GRAPHSEGITERATION
