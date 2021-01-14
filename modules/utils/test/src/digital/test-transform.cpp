#include <catch.hpp>

#include "graph-flow/utils/digital/shapes.h"
#include "graph-flow/utils/digital/transform.h"

using namespace GraphFlow::Utils::Digital::Transform;

TEST_CASE("bottomLeftBoundingBox","[digital]") {
  using namespace DGtal::Z2i;

  DigitalSet squareDS = GraphFlow::Utils::Digital::Shapes::square();
  Point padding(20, 20);

  DigitalSet firstQuadrantSquare =
      bottomLeftBoundingBoxAtOrigin(squareDS, padding);

  Point lb, ub;
  firstQuadrantSquare.computeBoundingBox(lb, ub);

  REQUIRE(squareDS.size() == firstQuadrantSquare.size());
  REQUIRE(lb == padding);
  REQUIRE(firstQuadrantSquare.domain().lowerBound() == Point(0, 0));
}