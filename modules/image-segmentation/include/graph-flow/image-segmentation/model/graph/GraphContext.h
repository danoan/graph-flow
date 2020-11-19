#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHCONTEXT_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHCONTEXT_H

#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/utils/digital.h>

#include "graph-flow/image-segmentation/model/GraphSegInput.h"

namespace GraphFlow::ImageSegmentation::Graph {
template <class TNeighborhood>
struct Context {
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DGtal::Z2i::Domain Domain;

  typedef TNeighborhood Neighborhood;

  Context(const GraphSegInput& gfi, const DigitalSet& ds,
          const Neighborhood& neighborhood)
      : gfi(gfi), neighborhood(neighborhood), ds(ds) {}

  Context(const Context& context) = delete;
  Context(Context&& context) = delete;

  const GraphSegInput& gfi;
  const DigitalSet& ds;

  Neighborhood neighborhood;
};

}  // namespace GraphFlow::ImageSegmentation::Graph

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_GRAPHCONTEXT_H
