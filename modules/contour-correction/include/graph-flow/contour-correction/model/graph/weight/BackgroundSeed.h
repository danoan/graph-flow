#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_BACKGROUND_SEED_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_BACKGROUND_SEED_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/utils/digital/misc.h>

namespace GraphFlow::ContourCorrection::Graph::Weight {
class BackgroundSeed : public GraphFlow::Core::TerminalWeight {
 public:
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef GraphFlow::Utils::Digital::Misc::DTL2 DTL2;

  BackgroundSeed(const DTL2& dtl2, int optBand, double ballRadius)
      : connectedToTarget(
            GraphFlow::Utils::Digital::Misc::level(dtl2, optBand, optBand - 1)),
        maxPenal(M_PI * pow(ballRadius, 2) * 1024) {}

  double operator()(const Point& p) {
    if (connectedToTarget(p))
      return maxPenal;
    else
      return 0;
  }

  double weight() const { return 1.0; }
  bool normalize() const { return false; }

  TerminalType type() const { return TerminalType::Target; }

 private:
  DigitalSet connectedToTarget;
  double maxPenal;
};
}  // namespace GraphFlow::ContourCorrection::Graph::Weight

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_BACKGROUND_SEED_H
