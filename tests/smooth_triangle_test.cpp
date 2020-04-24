#include "smooth_triangle.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("An intersection with a smooth triangle stores u/v") {
  const auto t = SmoothTriangle::Default();
  const Ray r{Point3{-0.2, 0.3, -2}, Vector3{0, 0, 1}};
  const auto xs = t.LocalIntersect(r);
  REQUIRE(xs.size() == 1);
  CHECK(xs[0].u == doctest::Approx(0.45));
  CHECK(xs[0].v == doctest::Approx(0.25));
}
