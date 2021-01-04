#include "graph-flow/core/FlowGraph.h"

namespace GraphFlow::Core {
FlowGraph::FlowGraph(const DigitalSet& vertexSet, TerminalWeightVector twv,
                     EdgeWeightVector ewv)
    : arcWeightMap(digraph),
      ntp(digraph),
      sourceNodes(vertexSet.domain()),
      twv(twv),
      ewv(ewv) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils;

  terminalSource = digraph.addNode();
  terminalTarget = digraph.addNode();
  for (auto p : vertexSet) addNode(p);

  setMax(vertexSet);

  for (int i = 0; i < twv.size(); ++i) {
    for (auto p : vertexSet) {
      auto& tw = twv[i];
      double factor;
      if (tw->normalize())
        factor = 1.0 / this->twvMax[i];
      else
        factor = 1.0;

      if (tw->type() == TerminalWeight::TerminalType::Source) {
        ListDigraph::Arc a = digraph.addArc(terminalSource, ptn[p]);
        double v = factor * tw->weight() * (*tw)(p);
        arcWeightMap[a] = v;
      } else {
        ListDigraph::Arc a = digraph.addArc(ptn[p], terminalTarget);
        double v = factor * tw->weight() * (*tw)(p);
        arcWeightMap[a] = v;
      }
    }
  }

  Point neighbors[4] = {Point(0, 1), Point(1, 0), Point(-1, 0), Point(0, -1)};
  std::set<Point> visited;
  for (int i = 0; i < ewv.size(); ++i) {
    for (auto p : vertexSet) {
      visited.insert(p);
      for (auto n : neighbors) {
        Point np = p + n;
        if (visited.find(np) != visited.end()) continue;

        if (vertexSet(np)) {
          ListDigraph::Arc a1 = digraph.addArc(ptn[p], ptn[np]);
          ListDigraph::Arc a2 = digraph.addArc(ptn[np], ptn[p]);

          auto& ew = ewv[i];
          double factor;
          if (ew->normalize())
            factor = 1.0 / this->ewvMax[i];
          else
            factor = 1.0;
          arcWeightMap[a1] = factor * ew->weight() * (*ew)(p, np);
          arcWeightMap[a2] = factor * ew->weight() * (*ew)(np, p);
        }
      }
    }
  }

  FlowComputer flow(digraph, arcWeightMap, terminalSource, terminalTarget);
  flow.run();

  cutValue = flow.flowValue();

  for (auto p : vertexSet) {
    if (flow.minCut(ptn[p])) sourceNodes.insert(p);
  }
}

void FlowGraph::addNode(const Point& p) {
  ptn[p] = digraph.addNode();
  ntp[ptn[p]] = p;
}

void FlowGraph::setMax(const DigitalSet& vertexSet) {
  twvMax.resize(this->twv.size());

  int i = 0;
  for (auto tw : twv) {
    double maxTerminalType = (*twv.begin())->operator()(*vertexSet.begin());

    for (auto p : vertexSet) {
      maxTerminalType = (*tw)(p) > maxTerminalType ? (*tw)(p) : maxTerminalType;
    }
    maxTerminalType = maxTerminalType == 0 ? 1 : maxTerminalType;

    twvMax[i++] = maxTerminalType;
  }

  ewvMax.resize(this->ewv.size());
  Point neighbors[4] = {Point(0, 1), Point(1, 0), Point(-1, 0), Point(0, -1)};
  i = 0;
  for (auto ew : ewv) {
    double maxEdgeType = 0;
    for (auto p : vertexSet) {
      for (auto n : neighbors) {
        Point np = p + n;
        if (vertexSet(np)) {
          maxEdgeType = (*ew)(p, np) > maxEdgeType ? (*ew)(p, np) : maxEdgeType;
        }
      }
    }
    maxEdgeType = maxEdgeType == 0 ? 1 : maxEdgeType;
    ewvMax[i++] = maxEdgeType;
  }
}

}  // namespace GraphFlow::Core