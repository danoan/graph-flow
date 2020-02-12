#ifndef GRAPHSEGITERATION
#define GRAPHSEGITERATION

#include <DGtal/helpers/StdDefs.h>

struct GraphSegIteration
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;

    GraphSegIteration(int iteration, double value, const DigitalSet& ds) :
    iteration(iteration),
    value(value),
    ds(ds) {}

    int iteration;
    double value;
    const DigitalSet& ds;
};
#endif //GRAPHSEGITERATION
