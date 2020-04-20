#include "cone.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("Intersecting a cone with a ray") {
  const Cone c;

  const std::vector<std::tuple<Point3, Vector3, scalar, scalar>> data{
      {{0, 0, -5}, {0, 0, 1}, 5, 5},
      {{0, 0, -5}, {1, 1, 1}, 8.66025, 8.66025},
      {{1, 1, -5}, {-0.5, -1, 1}, 4.55006, 49.44994}};

  for (const auto& [origin, direction, t1, t2] : data) {
    const Ray r{origin, Normalized(direction)};
    const auto xs = c.LocalIntersect(r);
    REQUIRE(xs.size() == 2);
    CHECK(xs[0].t == doctest::Approx(t1));
    CHECK(xs[1].t == doctest::Approx(t2));
  }
}

SCENARIO("Intersecting a cone with a ray parallel to one of its halves") {
  const Cone c;
  const Ray r{Point3{0, 0, -1}, Normalized(Vector3{0, 1, 1})};
  const auto xs = c.LocalIntersect(r);
  REQUIRE(xs.size() == 1);
  CHECK(xs[0].t == doctest::Approx(0.35355));
}

SCENARIO("Intersecting a cone's end caps") {
  const Cone c(-0.5, 0.5, true);
  const std::vector<std::tuple<Point3, Vector3, size_t>> data{
      {{0, 0, -5}, {0, 1, 0}, 0},
      {{0, 0, -0.25}, {0, 1, 1}, 2},
      {{0, 0, -0.25}, {0, 1, 0}, 4}};

  for (const auto& [origin, direction, count] : data) {
    const Ray r{origin, Normalized(direction)};
    const auto xs = c.LocalIntersect(r);
    REQUIRE(xs.size() == count);
  }
}

SCENARIO("Computing the normal vector on a cone") {
  const Cone c;
  const std::vector<std::tuple<Point3, Vector3>> data{
      {{0, 0, 0}, {0, 0, 0}},
      {{1, 1, 1}, {1, -kSqrt2, 1}},
      {{-1, -1, 0}, {-1, 1, 0}}};

  for (const auto& [point, normal] : data) {
    CHECK(c.LocalNormalAt(point) == normal);
  }
}