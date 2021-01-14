#include <catch.hpp>

#include "graph-flow/utils/digital/set-operations.h"
#include "graph-flow/utils/digital/shapes.h"

using namespace GraphFlow::Utils::Digital::SetOperations;

TEST_CASE("set difference", "[digital]") {
  using namespace DGtal::Z2i;

  DigitalSet square = GraphFlow::Utils::Digital::Shapes::square();
  DigitalSet ball = GraphFlow::Utils::Digital::Shapes::ball();

  DigitalSet difference(ball.domain());
  setDifference(difference, ball, square);

  REQUIRE(difference.size() == 92);
}

TEST_CASE("ball intersection", "[digital]") {
  using namespace DGtal::Z2i;
  
  DigitalSet square = GraphFlow::Utils::Digital::Shapes::square(1.0, 0, 0, 10);
  DigitalBallIntersection DBI(5, square);

  DigitalSet intersection(square.domain());
  DBI(intersection, Point(-7, 7));

  REQUIRE(intersection.size() == 26);
}