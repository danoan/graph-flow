#ifndef GRAPH_FLOW_APP_GRAPH_SEG_FOREGROUND_H
#define GRAPH_FLOW_APP_GRAPH_SEG_FOREGROUND_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/image/CVMatDistribution.h"

namespace App::Graph::Weight {
class Foreground : public GraphFlow::Core::TerminalWeight {
 public:
  Foreground(App::Image::CVMatDistribution &frgDistr, double regionalWeight) : frgDistr(frgDistr), regionalWeight(regionalWeight) {}

  double operator()(const Point &p) {
    return -log(frgDistr(frgDistr.img.rows - p[1], p[0]));
  }

  double weight() const { return regionalWeight; }
  bool normalize() const { return true; }

  TerminalType type() const { return TerminalType::Target; }

 private:
  App::Image::CVMatDistribution frgDistr;
  double regionalWeight;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_FOREGROUND_H
