#include <graph-flow/utils/digital/misc.h>
#include <graph-flow/utils/digital/shapes.h>

#include "catch.hpp"

using namespace GraphFlow::Utils::Digital::Misc;

TEST_CASE("distance transform", "[digital]") {
  using namespace DGtal::Z2i;

  double h = 1.0;
  double radius = 10;

  DigitalSet _ball = GraphFlow::Utils::Digital::Shapes::ball(h, 0, 0, radius);
  const Domain& ballDomain = _ball.domain();

  Point border(20, 20);
  Domain domain(ballDomain.lowerBound() - border,
                ballDomain.upperBound() + border);

  DigitalSet ball(domain);
  ball.insert(_ball.begin(), _ball.end());

  SECTION("interior distance transform") {
    auto dtInn = interiorDistanceTransform(domain, ball);
    std::map<Point, double> pointDistanceInn = {{Point(0, radius), 1},
                                                {Point(0, radius + 1), 0}};

    for (auto p : pointDistanceInn) {
      REQUIRE(dtInn(p.first) == p.second);
    }
  }

  SECTION("exterior distance transform") {
    auto dtOut = exteriorDistanceTransform(domain, ball);
    std::map<Point, double> pointDistanceOut = {{Point(0, radius + 1), 1},
                                                {Point(0, radius), 0}};

    for (auto p : pointDistanceOut) {
      REQUIRE(dtOut(p.first) == p.second);
    }
  }

  SECTION("k-level distance band") {
    auto dtInn = interiorDistanceTransform(domain, ball);
    DigitalSet kLevelSet = level(dtInn, 5, 0);
    REQUIRE(kLevelSet.size() == 236);
  }
}