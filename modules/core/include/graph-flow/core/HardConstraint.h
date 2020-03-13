#ifndef GRAPH_FLOW_HARDCONSTRAINTINTERFACE_H
#define GRAPH_FLOW_HARDCONSTRAINTINTERFACE_H

#include "HardConstraintElement.h"

namespace GraphFlow::Core
{
    class HardConstraint
    {
    public:
        typedef std::vector<HardConstraintElement>::const_iterator HardConstraintIterator;

        virtual bool normalize() const=0;
        virtual HardConstraintIterator begin()=0;
        virtual HardConstraintIterator end()=0;
        virtual ~HardConstraint(){}
    };
}

#endif //GRAPH_FLOW_HARDCONSTRAINTINTERFACE_H
