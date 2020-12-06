#include <graph-flow/utils/string.h>

#include <catch.hpp>

using namespace GraphFlow::Utils::String;

TEST_CASE("fixedStrLength", "[string]") {
  std::string O1 = fixedStrLength(10, "the sky is blue");
  REQUIRE(O1 == "the sky is blue");

  std::string O2 = fixedStrLength(10, "sky");
  REQUIRE(O2 == "sky       ");

  std::string O3 = fixedStrLength(10, 10.341,3);
  REQUIRE(O3 == "10.341    ");
}

TEST_CASE("nDigitsString", "[string]") {
  std::string O1 = nDigitsString(10, 3);
  REQUIRE(O1 == "010");

  std::string O2 = nDigitsString(10, 1);
  REQUIRE(O2 == "10");
}