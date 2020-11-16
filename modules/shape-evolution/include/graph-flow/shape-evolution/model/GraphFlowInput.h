#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHFLOWINPUT_H
#define GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHFLOWINPUT_H

#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/core/TerminalWeight.h>

namespace GraphFlow::ShapeEvolution {
class GraphFlowInput {
 public:
  typedef DGtal::Z2i::DigitalSet DigitalSet;

 private:
  void init() {
    iterations = 10;
    radius = 5;
    vradius = radius;
    h = 0.25;
    alpha = 0.01;
    beta = 1.0;

    optBand = 2;
    border = 20;
    tolerance = -1;

    nThreads = 4;
    neighborhoodSize = 2;
  }

 public:
  GraphFlowInput(DigitalSet &inputDS) : inputDS(inputDS) { init(); }

 public:
  int iterations;
  double radius;
  double vradius;  // Validation radius
  double h;
  double alpha;
  double beta;

  int optBand;
  int border;
  double tolerance;

  int nThreads;
  int neighborhoodSize;

  DigitalSet inputDS;
};
}  // namespace GraphFlow::ShapeEvolution

#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_GRAPHFLOWINPUT_H
