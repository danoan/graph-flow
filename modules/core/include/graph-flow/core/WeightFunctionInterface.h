#ifndef GRAPH_FLOW_CORE_WEIGHTFUNCTIONINTERFACE_H
#define GRAPH_FLOW_CORE_WEIGHTFUNCTIONINTERFACE_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Core
{
    class WeightFunctionInterface
    {
    public:
        virtual double operator()(const DGtal::Z2i::Point& p, bool sourceTarget)=0;
    };
}

#endif //GRAPH_FLOW_CORE_WEIGHTFUNCTIONINTERFACE_H
