#ifndef GRAPH_FLOW_APP_GRAPH_SEG_BACKGROUND_H
#define GRAPH_FLOW_APP_GRAPH_SEG_BACKGROUND_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/image/CVMatDistribution.h"

namespace App::Graph::Weight {
class Background : public GraphFlow::Core::TerminalWeight {
 public:
  Background(App::Image::CVMatDistribution &bkgDistr, double regionalWeight) : bkgDistr(bkgDistr), regionalWeight(regionalWeight) {}

  double operator()(const Point &p) {
    return -log(bkgDistr(bkgDistr.img.rows - p[1], p[0]));
  }

  double weight() const { return regionalWeight; }
  bool normalize() const { return true; }

  TerminalType type() const { return TerminalType::Source; }

 private:
  App::Image::CVMatDistribution bkgDistr;
  double regionalWeight;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_BACKGROUND_H
