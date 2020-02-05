#ifndef GRAPH_FLOW_CORE_ARCPENALIZATIONINTERFACE_H
#define GRAPH_FLOW_CORE_ARCPENALIZATIONINTERFACE_H

#include <DGtal/helpers/StdDefs.h>
#include "ArcPenalizationElement.h"

namespace GraphFlow::Core
{
    class ArcPenalizationInterface
    {
    public:

        typedef std::vector<ArcPenalizationElement>::const_iterator ArcPenalizationIterator;

        virtual ArcPenalizationIterator begin()=0;
        virtual ArcPenalizationIterator end()=0;
    };
}

#endif //GRAPH_FLOW_CORE_ARCPENALIZATIONINTERFACE_H
