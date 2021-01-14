#include <graph-flow/utils/digital/shapes.h>

#include "catch.hpp"

using namespace GraphFlow::Utils::Digital::Shapes;

TEST_CASE("resolve shape accept all types", "[digital]") {
  using namespace DGtal::Z2i;

  std::map<std::string, size_t> sizesDict = {
      /*{"triangle", 521}, expecting correction in DGtal1.2 to be relased*/  
      {"square", 841}, {"pentagon", 960},
      {"heptagon", 1107}, {"ball", 1257},  {"ellipse", 626},
      {"flower", 1867},   {"bean", 1574} };

  for (auto p : sizesDict) {
    std::string shapeName = p.first;
    size_t size = p.second;

    DigitalSet shape = resolveShape(shapeName, 1.0, 20);
    REQUIRE(shape.size() == size);
  }
}