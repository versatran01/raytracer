#include "color.h"

#include "doctest/doctest.h"

using namespace rt;

SCENARIO("Colors are (r, g, b) tuples") {
  const Color c(-0.5, 0.4, 1.7);
  CHECK(c.r() == -0.5);
  CHECK(c.g() == 0.4);
  CHECK(c.b() == 1.7);
}

SCENARIO("Operations on colors") {
  const Color c1(0.9, 0.6, 0.7);
  const Color c2(0.7, 0.1, 0.2);
  CHECK((c1 + c2).isApprox(Color(1.6, 0.7, 0.9)));
  CHECK((c1 - c2).isApprox(Color(0.2, 0.5, 0.5)));
  CHECK(c1 * 2 == Color(1.8, 1.2, 1.4));
  CHECK((c1 * c2).isApprox(Color(0.63, 0.06, 0.14)));
}