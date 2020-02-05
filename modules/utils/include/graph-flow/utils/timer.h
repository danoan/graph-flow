#ifndef GRAPH_FLOW_UTILS_TIMER_H
#define GRAPH_FLOW_UTILS_TIMER_H

#include <ostream>
#include <boost/date_time.hpp>

namespace GraphFlow::Utils
{
    struct Timer
    {
        boost::posix_time::ptime startTime;
        boost::posix_time::ptime endTime;

        void start();
        void end(std::ostream& os);
    };

}

#endif //GRAPH_FLOW_UTILS_TIMER_H
