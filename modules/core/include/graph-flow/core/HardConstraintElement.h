#ifndef GRAPH_FLOW_HARDCONTRAINTELEMENT_H
#define GRAPH_FLOW_HARDCONTRAINTELEMENT_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Core
{
    class HardConstraintElement
    {
    public:
        enum ArcType{ToTarget,FromSource,Replace,Parallel};
        typedef DGtal::Z2i::Point Point;

        HardConstraintElement(ArcType at,const Point& source, const Point& target, double value):
        arcType(at),
        source(source),
        target(target),
        value(value){}

        ArcType arcType;
        Point source;
        Point target;
        double value;
    };
}

#endif //GRAPH_FLOW_HARDCONTRAINTELEMENT_H
