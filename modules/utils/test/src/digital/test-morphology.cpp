#include <graph-flow/utils/digital/morphology.h>
#include <graph-flow/utils/digital/shapes.h>

#include "catch.hpp"

using namespace GraphFlow::Utils::Digital::Morphology;

TEST_CASE("morphology", "[digital]") {
  using namespace DGtal::Z2i;

  double h = 1.0;
  double radius = 10;

  DigitalSet _ball = GraphFlow::Utils::Digital::Shapes::ball(h, 0, 0, radius);
  Domain extDomain(_ball.domain().lowerBound() - Point(10, 10),
                   _ball.domain().upperBound() + Point(10, 10));

  DigitalSet ball(extDomain);
  ball.insert(_ball.begin(), _ball.end());

  SECTION("default dilation and erosion") {
    DigitalSet dilatedBall(extDomain);

    dilate(dilatedBall, ball, 1);

    DigitalSet erodedBall(extDomain);
    erode(erodedBall, ball, 1);

    REQUIRE(dilatedBall.size() > ball.size());
    REQUIRE(erodedBall.size() < ball.size());
  }

  SECTION("user-defined structuring element dilation and erosion") {
    DigitalSet dilatedBall(extDomain);

    dilate(dilatedBall, ball, StructuringElement(StructuringElement::RECT, 3),
           1);

    DigitalSet erodedBall(extDomain);
    erode(erodedBall, ball, StructuringElement(StructuringElement::CROSS, 3),
          1);

    REQUIRE(dilatedBall.size() > ball.size());
    REQUIRE(erodedBall.size() < ball.size());
  }  
}
