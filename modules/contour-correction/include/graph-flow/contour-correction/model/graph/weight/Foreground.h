#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_FOREGROUND_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_FOREGROUND_H

#include <graph-flow/core/TerminalWeight.h>

#include "graph-flow/contour-correction/model/image/CVMatDistribution.h"

namespace GraphFlow::ContourCorrection::Graph::Weight {
class Foreground : public GraphFlow::Core::TerminalWeight {
 public:
 typedef GraphFlow::Core::NormalizationGroup NormalizationGroup;

  Foreground(Image::CVMatDistribution &frgDistr, double regionalWeight)
      : frgDistr(frgDistr), regionalWeight(regionalWeight) {}

  double operator()(const Point &p) {
    return -log(frgDistr(frgDistr.img.rows - p[1]-1, p[0]));
  }

  double weight() const { return regionalWeight; }
  NormalizationGroup normalizationGroup() const { return NormalizationGroup::DataRelated; }

  TerminalType type() const { return TerminalType::Target; }

 private:
  Image::CVMatDistribution frgDistr;
  double regionalWeight;
};
}  // namespace GraphFlow::ContourCorrection::Graph::Weight

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_FOREGROUND_H
