#ifndef GRAPH_FLOW_TERMINALWEIGHT_H
#define GRAPH_FLOW_TERMINALWEIGHT_H

#include <DGtal/helpers/StdDefs.h>
#include "NormalizationGroup.h"

namespace GraphFlow::Core {
class TerminalWeight {
 public:
  typedef DGtal::Z2i::Point Point;
  enum TerminalType { Source, Target };

  virtual double operator()(const Point& p) = 0;
  virtual double weight() const = 0;
  virtual TerminalType type() const = 0;
  virtual NormalizationGroup normalizationGroup() const = 0;
  virtual ~TerminalWeight() {}
};
}  // namespace GraphFlow::Core

#endif  // GRAPH_FLOW_TERMINALWEIGHT_H
