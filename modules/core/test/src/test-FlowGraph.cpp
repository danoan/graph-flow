#include <graph-flow/core/FlowGraph.h>

#include <unordered_map>

#include "catch.hpp"

using namespace GraphFlow::Core;

class MyTerminalWeight : public TerminalWeight {
 private:
  TerminalType m_terminalType;
  std::set<Point> m_connectedToTerminal;

 public:
 typedef GraphFlow::Core::NormalizationGroup NormalizationGroup;

  MyTerminalWeight(TerminalType terminalType,
                   const std::set<Point>& connectedToTerminal)
      : m_terminalType(terminalType),
        m_connectedToTerminal(connectedToTerminal) {}

  double operator()(const Point& p) {
    if (m_connectedToTerminal.find(p) != m_connectedToTerminal.end()) {
      return 100;
    } else {
      return 0;
    }
  }

  double weight() const { return 1.0; }

  TerminalType type() const { return m_terminalType; }

  NormalizationGroup normalizationGroup() const { return NormalizationGroup::None; }

  ~MyTerminalWeight() = default;
};

class MyEdgeWeight : public EdgeWeight {
 private:
  std::unordered_map<Point, double> m_pointWeights;

 public:
 typedef GraphFlow::Core::NormalizationGroup NormalizationGroup;

  MyEdgeWeight(const std::unordered_map<Point, double>& pointWeights)
      : m_pointWeights(pointWeights) {}
  double operator()(const Point& p1, const Point& p2) {
    return m_pointWeights[p1] + m_pointWeights[p2];
  }
  double weight() const { return 1.0; }
  NormalizationGroup normalizationGroup() const { return NormalizationGroup::None; }
  ~MyEdgeWeight() = default;
};

TEST_CASE("initialize FlowGraph", "[core][FlowGraph]") {
  /*

  Graph topology

      0 - 0 - 0
      |   |   |
  0 - 0 - 0 - 0 - 0
  |   |       |   |
  0 - 0       0 - 0
  |   |       |   |
  0 - 0 - 0 - 0 - 0
      |   |   |
      0 - 0 - 0

  */
  using namespace DGtal::Z2i;

  Domain domain(Point(0, 0), Point(10, 10));
  DigitalSet vertexSet(domain);

  Point p23(3, 2);
  Point p24(4, 2);
  Point p25(5, 2);

  Point p32(2, 3);
  Point p33(3, 3);
  Point p34(4, 3);
  Point p35(5, 3);
  Point p36(6, 3);

  Point p42(2, 4);
  Point p43(3, 4);
  Point p45(5, 4);
  Point p46(6, 4);

  Point p52(2, 5);
  Point p53(3, 5);
  Point p54(4, 5);
  Point p55(5, 5);
  Point p56(6, 5);

  Point p63(3, 6);
  Point p64(4, 6);
  Point p65(5, 6);

  vertexSet.insert(p23);
  vertexSet.insert(p24);
  vertexSet.insert(p25);

  vertexSet.insert(p32);
  vertexSet.insert(p33);
  vertexSet.insert(p34);
  vertexSet.insert(p35);
  vertexSet.insert(p36);

  vertexSet.insert(p42);
  vertexSet.insert(p43);
  vertexSet.insert(p45);
  vertexSet.insert(p46);

  vertexSet.insert(p52);
  vertexSet.insert(p53);
  vertexSet.insert(p54);
  vertexSet.insert(p55);
  vertexSet.insert(p56);

  vertexSet.insert(p63);
  vertexSet.insert(p64);
  vertexSet.insert(p65);

  std::unordered_map<Point, double> pointMap = {
      {p23, 4},  {p24, 4},  {p25, 4}, {p32, 4},  {p33, 40},
      {p34, 40}, {p35, 40}, {p36, 4}, {p42, 4},  {p43, 40},
      {p45, 40}, {p46, 4},  {p52, 4}, {p53, 40}, {p54, 40},
      {p55, 40}, {p56, 4},  {p63, 4}, {p64, 4},  {p65, 4}};

  std::set<Point> connectedToSource{p33, p34, p35, p43, p45, p53, p54, p55};
  std::set<Point> connectedToTarget{p32, p23, p24, p25, p36, p42,
                                    p46, p52, p56, p63, p64, p65};

  std::vector<TerminalWeight*> twv = {
      new MyTerminalWeight(TerminalWeight::TerminalType::Source,
                           connectedToSource),
      new MyTerminalWeight(TerminalWeight::TerminalType::Target,
                           connectedToTarget)};

  std::vector<EdgeWeight*> tev = {new MyEdgeWeight(pointMap)};

  FlowGraph fg(vertexSet, twv, tev);
  REQUIRE(fg.cutValue == 528);

  for (auto p : fg.sourceNodes) {
    REQUIRE_FALSE(connectedToSource.find(p) == connectedToSource.end());
  }

  for(auto t: twv) delete t;
  for(auto t: tev) delete t;
}