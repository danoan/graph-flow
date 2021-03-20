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
    auto& tw = twv[i];
    NormalizationGroup NG = tw->normalizationGroup();
    double factor = normalizationGroupFactors[NG];

    for (auto p : vertexSet) {
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
    auto& ew = ewv[i];
    NormalizationGroup NG = ew->normalizationGroup();
    double factor = normalizationGroupFactors[NG];

    for (auto p : vertexSet) {
      visited.insert(p);
      for (auto n : neighbors) {
        Point np = p + n;
        if (visited.find(np) != visited.end()) continue;

        if (vertexSet(np)) {
          ListDigraph::Arc a1 = digraph.addArc(ptn[p], ptn[np]);
          ListDigraph::Arc a2 = digraph.addArc(ptn[np], ptn[p]);

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
  normalizationGroupFactors.resize(NormalizationGroup::ENUM_LENGTH);
  normalizationGroupFactors[NormalizationGroup::None] = 1;

  int i = 0;
  for (auto tw : twv) {
    NormalizationGroup NG = tw->normalizationGroup();
    if (NG == NormalizationGroup::None) {
      continue;
    }

    double maxTerminalType = (*twv.begin())->operator()(*vertexSet.begin());

    for (auto p : vertexSet) {
      maxTerminalType = (*tw)(p) > maxTerminalType ? (*tw)(p) : maxTerminalType;
    }
    maxTerminalType = maxTerminalType == 0 ? 1 : maxTerminalType;

    if( maxTerminalType > normalizationGroupFactors[NG] ){
      normalizationGroupFactors[NG] = maxTerminalType;
    }
  }

  Point neighbors[4] = {Point(0, 1), Point(1, 0), Point(-1, 0), Point(0, -1)};
  i = 0;
  for (auto ew : ewv) {
    NormalizationGroup NG = ew->normalizationGroup();
    if (NG == NormalizationGroup::None) {
      continue;
    }

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

    if(maxEdgeType > normalizationGroupFactors[NG]){
      normalizationGroupFactors[NG] = maxEdgeType;
    }
  }

  for(int i=0;i<NormalizationGroup::ENUM_LENGTH;++i){
    normalizationGroupFactors[i] = 1.0/normalizationGroupFactors[i];
  }


}

}  // namespace GraphFlow::Core