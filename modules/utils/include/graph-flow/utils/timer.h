#ifndef GRAPH_FLOW_UTILS_TIMER_H
#define GRAPH_FLOW_UTILS_TIMER_H

#include <boost/date_time.hpp>
#include <ostream>

namespace GraphFlow::Utils {
struct Timer {
  boost::posix_time::ptime startTime;
  boost::posix_time::ptime endTime;

  void start();
  void end(std::ostream& os);
};

}  // namespace GraphFlow::Utils

#endif  // GRAPH_FLOW_UTILS_TIMER_H
