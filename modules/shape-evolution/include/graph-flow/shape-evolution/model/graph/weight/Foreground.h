#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_FOREGROUND_H
#define GRAPH_FLOW_SHAPE_EVOLUTION_FOREGROUND_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/utils/digital/misc.h>

namespace GraphFlow::ShapeEvolution::Graph::Weight {
class Foreground : public GraphFlow::Core::TerminalWeight {
 public:
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef GraphFlow::Utils::Digital::Misc::DTL2 DTL2;

  Foreground(const DTL2 &dtl2, int optBand, double ballRadius)
      : connectedToSource(
            GraphFlow::Utils::Digital::Misc::level(dtl2, optBand, optBand - 1)),
        maxPenal(M_PI * pow(ballRadius, 2) * 1024) {}

  double operator()(const Point &p) {
    if (connectedToSource(p))
      return maxPenal;
    else
      return 0;
  }

  double weight() const { return 1.0; }
  bool normalize() const { return false; }

  TerminalType type() const { return TerminalType::Source; }

 private:
  DigitalSet connectedToSource;
  double maxPenal;
};
}  // namespace GraphFlow::ShapeEvolution::Graph::Weight

#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_FOREGROUND_H
