//
// Created by dantu on 05/02/20.
//

#ifndef GRAPH_FLOW_CORE_ARCPENALIZATIONELEMENT_H
#define GRAPH_FLOW_CORE_ARCPENALIZATIONELEMENT_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Core
{

    struct ArcPenalizationElement
    {
        enum ArcType{ToTarget,FromSource,Replace,Parallel};
        typedef DGtal::Z2i::Point Point;

        ArcPenalizationElement(ArcType at,const Point& source, const Point& target, double value):
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

#endif //GRAPH_FLOW_CORE_ARCPENALIZATIONELEMENT_H
