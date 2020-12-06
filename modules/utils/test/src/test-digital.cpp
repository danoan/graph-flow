#include <graph-flow/utils/digital.h>

#include "catch.hpp"

using namespace GraphFlow::Utils::Digital;

TEST_CASE("resolve shape accept all types", "[digital]") {
  using namespace DGtal::Z2i;

  std::map<std::string, size_t> sizesDict = {
      {"triangle", 521},  {"square", 841}, {"pentagon", 960},
      {"heptagon", 1107}, {"ball", 1257},  {"ellipse", 626},
      {"flower", 1867},   {"bean", 1574},  {"wave", 417}};

  for (auto p : sizesDict) {
    std::string shapeName = p.first;
    size_t size = p.second;

    DigitalSet shape = resolveShape(shapeName, 1.0, 20);
    REQUIRE(shape.size() == size);
  }
}

TEST_CASE("distance transform", "[digital]") {
  using namespace DGtal::Z2i;

  double h = 1.0;
  double radius = 10;

  DigitalSet _ball = DIPaCUS::Shapes::ball(h, 0, 0, radius);
  const Domain& ballDomain = _ball.domain();

  Point border(20, 20);
  Domain domain(domain.lowerBound() - border, domain.upperBound() + border);

  DigitalSet ball(domain);
  ball.insert(_ball.begin(), _ball.end());
  auto dtInn = interiorDistanceTransform(domain, ball);
  std::map<Point, double> pointDistanceInn = {{Point(0, radius), 1},
                                              {Point(0, radius + 1), 0}};

  for (auto p : pointDistanceInn) {
    REQUIRE(dtInn(p.first) == p.second);
  }
}

TEST_CASE("morpholody", "[digital]") {
  using namespace DGtal::Z2i;

  double h = 1.0;
  double radius = 10;

  DigitalSet ball = DIPaCUS::Shapes::ball(h, 0, 0, radius);
  DigitalSet dilatedBall = dilate(ball, 1);
  DigitalSet erodedBall = erode(ball, 1);

  REQUIRE(dilatedBall.size() > ball.size());
  REQUIRE(erodedBall.size() < ball.size());
}
