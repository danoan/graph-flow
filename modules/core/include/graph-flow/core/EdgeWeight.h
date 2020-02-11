#ifndef GRAPH_FLOW_EDGEWEIGHT_H
#define GRAPH_FLOW_EDGEWEIGHT_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Core
{
    class EdgeWeight
    {
    public:
        typedef DGtal::Z2i::Point Point;
        virtual double operator()(const Point& p1, const Point& p2)=0;
    };
}

#endif //GRAPH_FLOW_EDGEWEIGHT_H
