#include <graph-flow/utils/timer.h>

#include <catch.hpp>

using namespace GraphFlow::Utils;

TEST_CASE("start and end timer", "[timer]") {
  Timer t;

  std::stringstream ss;
  t.start();

  double x = 1;
  for (int i = 1; i < 1e6; ++i) {
    if (i % 2 == 0)
      x += i;
    else
      x -= i;
  }

  t.end(ss);
  REQUIRE(ss.str().size() > 0);
}