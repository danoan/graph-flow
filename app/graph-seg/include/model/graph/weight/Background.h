#ifndef GRAPH_FLOW_BACKGROUND_H
#define GRAPH_FLOW_BACKGROUND_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/CVMatDistribution.h"

namespace Graph::Weight {
class Background : public GraphFlow::Core::TerminalWeight {
 public:
  Background(CVMatDistribution &bkgDistr, double regionalWeight) : bkgDistr(bkgDistr), regionalWeight(regionalWeight) {}

  double operator()(const Point &p) {
    return -log(bkgDistr(bkgDistr.img.rows - p[1], p[0]));
  }

  double weight() const { return regionalWeight; }
  bool normalize() const { return true; }

  TerminalType type() const { return TerminalType::Source; }

 private:
  CVMatDistribution bkgDistr;
  double regionalWeight;
};
}

#endif //GRAPH_FLOW_BACKGROUND_H
