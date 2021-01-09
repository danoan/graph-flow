#include <graph-flow/utils/digital/shapes.h>
#include <graph-flow/utils/digital/transform.h>
#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>

#include "catch.hpp"

using namespace GraphFlow::Core::Neighborhood;

int countNeighbors(const Morphology& M) {
  int c = 0;
  for (auto it = M.begin(); it != M.end(); ++it, ++c)
    ;
  return c;
}

TEST_CASE("morphology neighborhood with size zero lifecycle",
          "[core][neighborhood]") {
  using namespace DGtal::Z2i;
  Morphology M(Morphology::MorphologyElement::CIRCLE, 0);

  SECTION("check number of blueprints") { REQUIRE(countNeighbors(M) == 1); }

  SECTION("check blueprints are the right type") {
    REQUIRE((*M.begin()).operationType == Morphology::Blueprint::None);
  }

  SECTION("evaluate candidate") {
    DigitalSet _shape = GraphFlow::Utils::Digital::Shapes::ball(0.5);
    DigitalSet shape =
        GraphFlow::Utils::Digital::Transform::bottomLeftBoundingBoxAtOrigin(_shape);

    DigitalSet out(shape.domain());
    M.evaluateCandidate(out, *M.begin(), shape);
    REQUIRE(out.size() == shape.size());
  }
}

TEST_CASE("morphology neighborhood with size greater than zero lifecycle",
          "[core][neighborhood]") {
  using namespace DGtal::Z2i;
  Morphology M(Morphology::MorphologyElement::CIRCLE, 2);

  SECTION("check number of blueprints") { REQUIRE(countNeighbors(M) == 5); }

  Morphology::Blueprint::OperationType expectedTypes[5] = {
      Morphology::Blueprint::None, Morphology::Blueprint::Erosion,
      Morphology::Blueprint::Dilation, Morphology::Blueprint::Erosion,
      Morphology::Blueprint::Dilation};

  SECTION("check blueprints are the right type") {
    int i = 0;
    for (auto it = M.begin(); it != M.end(); ++it, ++i) {
      REQUIRE(it->operationType == expectedTypes[i]);
    }
  }

  SECTION("evaluate candidate") {
    DigitalSet _shape = GraphFlow::Utils::Digital::Shapes::ball(0.5);
    DigitalSet shape =
        GraphFlow::Utils::Digital::Transform::bottomLeftBoundingBoxAtOrigin(_shape);
   
    int i = 0;
    for (auto it = M.begin(); it != M.end(); ++it, ++i) {
      CAPTURE(i);
      
      DigitalSet out(shape.domain());
      M.evaluateCandidate(out, *it, shape);
      if (expectedTypes[i] == Morphology::Blueprint::None) {
        REQUIRE(out.size() == shape.size());
      } else if (expectedTypes[i] == Morphology::Blueprint::Dilation) {
        REQUIRE(out.size() > shape.size());
      } else if (expectedTypes[i] == Morphology::Blueprint::Erosion) {
        REQUIRE(out.size() < shape.size());
      }
    }
  }
}