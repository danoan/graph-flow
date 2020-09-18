#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_CANDIDATE_H_
#define GRAPH_FLOW_APP_GRAPH_FLOW_CANDIDATE_H_

#include <DGtal/helpers/StdDefs.h>

namespace App{
struct Candidate{
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  DigitalSet* ds;
  double value;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_FLOW_CANDIDATE_H_
