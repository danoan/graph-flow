#ifndef GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_CANDIDATE_H_
#define GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_CANDIDATE_H_

#include <DGtal/helpers/StdDefs.h>

namespace App{
struct Candidate{
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  int id;
  DigitalSet* ds;
  double value;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_INCLUDE_MODEL_CANDIDATE_H_
