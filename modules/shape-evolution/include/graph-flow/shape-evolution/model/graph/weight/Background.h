#ifndef GRAPH_FLOW_SHAPE_EVOLUTION_BACKGROUND_H
#define GRAPH_FLOW_SHAPE_EVOLUTION_BACKGROUND_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/utils/digital/misc.h>

namespace GraphFlow::ShapeEvolution::Graph::Weight {
class Background : public GraphFlow::Core::TerminalWeight {
 public:
  typedef GraphFlow::Core::NormalizationGroup NormalizationGroup;
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef GraphFlow::Utils::Digital::Misc::DTL2 DTL2;

  Background(const DTL2 &dtl2, int optBand, double ballRadius)
      : connectedToTarget(
            GraphFlow::Utils::Digital::Misc::level(dtl2, optBand, optBand - 1)),
        maxPenal(M_PI * pow(ballRadius, 2) * 1024) {}

  double operator()(const Point &p) {
    if (connectedToTarget(p))
      return maxPenal;
    else
      return 0;
  }

  double weight() const { return 1.0; }
  NormalizationGroup normalizationGroup() const { return NormalizationGroup::None; }

  TerminalType type() const { return TerminalType::Target; }

 private:
  DigitalSet connectedToTarget;
  double maxPenal;
};
}  // namespace GraphFlow::ShapeEvolution::Graph::Weight

#endif  // GRAPH_FLOW_SHAPE_EVOLUTION_GRAPH_FLOW_BACKGROUND_H
