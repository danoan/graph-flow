#include <DIPaCUS/base/Shapes.h>
#include <graph-flow/utils/energy.h>

#include <catch.hpp>

using namespace GraphFlow::Utils::Energy;

TEST_CASE("elastica", "[energy]") {
  double h = 0.25;
  double R1 = 8;
  double R2 = 16;

  DigitalSet B1 = DIPaCUS::Shapes::ball(h, 0, 0, R1);
  DigitalSet B2 = DIPaCUS::Shapes::ball(h, 0, 0, R2);

  double estimationBallRadius = 5;

  SECTION("no length penalization") {
    double v1 = elastica(B1, estimationBallRadius, h, 0, 1);
    double v2 = elastica(B2, estimationBallRadius, h, 0, 1);

    REQUIRE(v1 > v2);
  }

  SECTION("B1 is optimum") {
    double a = 1.0 / (R1 * R1);

    double v1 = elastica(B1, estimationBallRadius, h, a, 1);
    double v2 = elastica(B2, estimationBallRadius, h, a, 1);

    REQUIRE(v1 < v2);
  }

  SECTION("B2 is optimum") {
    double a = 1.0 / (R2 * R2);

    double v1 = elastica(B1, estimationBallRadius, h, a, 1);
    double v2 = elastica(B2, estimationBallRadius, h, a, 1);

    REQUIRE(v2 < v1);
  }
}