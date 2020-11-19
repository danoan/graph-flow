#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHSEGINPUT_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHSEGINPUT_H

#include <DGtal/helpers/StdDefs.h>

#include "graph-flow/image-segmentation/model/image/DataDistribution.h"

namespace GraphFlow::ImageSegmentation {
class GraphSegInput {
 public:
  typedef DGtal::Z2i::DigitalSet DigitalSet;

 private:
  void init() {
    iterations = 10;
    radius = 5;
    vradius = radius;
    h = 1.0;
    alpha = 0.01;

    regionalTermWeight = 1;
    curvatureTermWeight = 0.5;

    optBand = 2;
    grabcutIterations = 1;
    tolerance = -1;

    nThreads = 4;
    neighborhoodSize = 2;
  }

 public:
  GraphSegInput(const DigitalSet &inputDS,
                const Image::DataDistribution &dataDistribution)
      : inputDS(inputDS), dataDistribution(dataDistribution) {
    init();
  }

  int iterations;
  double radius;
  double vradius; //Validation radius
  double h;

  double alpha;
  int optBand;
  double tolerance;
  int grabcutIterations;

  double regionalTermWeight;
  double curvatureTermWeight;
  int nThreads;
  int neighborhoodSize;

  const DigitalSet &inputDS;
  const Image::DataDistribution &dataDistribution;
};
}  // namespace GraphFlow::ImageSegmentation
#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHSEGINPUT_H
