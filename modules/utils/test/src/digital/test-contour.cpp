#include "graph-flow/utils/digital/contour.h"
#include "graph-flow/utils/digital/shapes.h"

#include "catch.hpp"

using namespace GraphFlow::Utils::Digital::Contour;

TEST_CASE("compute boundary curve","[digital]"){
  using namespace DGtal::Z2i;
  
  DigitalSet ball = GraphFlow::Utils::Digital::Shapes::ball();
  Curve curve;

  computeBoundaryCurve(curve, ball);
  REQUIRE( curve.size()==84 );
}