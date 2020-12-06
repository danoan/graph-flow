#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_BACKGROUND_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_BACKGROUND_H

#include <graph-flow/core/TerminalWeight.h>

#include "graph-flow/contour-correction/model/image/CVMatDistribution.h"

namespace GraphFlow::ContourCorrection::Graph::Weight {
class Background : public GraphFlow::Core::TerminalWeight {
 public:
  Background(Image::CVMatDistribution &bkgDistr, double regionalWeight)
      : bkgDistr(bkgDistr), regionalWeight(regionalWeight) {}

  double operator()(const Point &p) {
    return -log(bkgDistr(bkgDistr.img.rows - p[1], p[0]));
  }

  double weight() const { return regionalWeight; }
  bool normalize() const { return true; }

  TerminalType type() const { return TerminalType::Source; }

 private:
  Image::CVMatDistribution bkgDistr;
  double regionalWeight;
};
}  // namespace GraphFlow::ContourCorrection::Graph::Weight

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_BACKGROUND_H
