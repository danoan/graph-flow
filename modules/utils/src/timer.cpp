#include "graph-flow/utils/timer.h"

namespace GraphFlow::Utils
{

    void Timer::start()
    {
        startTime = boost::posix_time::microsec_clock::local_time();
    }

    void Timer::end(std::ostream& os)
    {
        endTime = boost::posix_time::microsec_clock::local_time();

        boost::posix_time::time_duration diff = endTime - startTime;
        os << diff.total_seconds() << "s " << diff.total_milliseconds() << "ms " << diff.total_microseconds() << "us \n";
    }
}