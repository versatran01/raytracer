#include "rt/cylinder.h"

#include <doctest/doctest.h>

namespace {

using namespace rt;

SCENARIO("A ray misses a cylinder") {
  const Cylinder c;

  const std::vector<std::tuple<Point3, Vector3>> data{
      {{1, 0, 0}, {0, 1, 0}}, {{0, 0, 0}, {0, 1, 0}}, {{0, 0, -5}, {1, 1, 1}}};

  for (const auto& [origin, direction] : data) {
    const Ray r{origin, Normalized(direction)};
    CHECK(c.LocalIntersect(r).empty());
  }
}

SCENARIO("A ray strikes a cylinder") {
  const Cylinder c;

  const std::vector<std::tuple<Point3, Vector3, scalar, scalar>> data{
      {{1, 0, -5}, {0, 0, 1}, 5, 5},
      {{0, 0, -5}, {0, 0, 1}, 4, 6},
      {{0.5, 0, -5}, {0.1, 1, 1}, 6.80798, 7.08872}};

  for (const auto& [origin, direction, t1, t2] : data) {
    const Ray r{origin, Normalized(direction)};
    const auto xs = c.LocalIntersect(r);
    REQUIRE(xs.size() == 2);
    CHECK(xs[0].t == doctest::Approx(t1));
    CHECK(xs[1].t == doctest::Approx(t2));
  }
}

SCENARIO("Normal vector on a cylinder") {
  const Cylinder c;
  const std::vector<std::tuple<Point3, Vector3>> data{{{1, 0, 0}, {1, 0, 0}},
                                                      {{0, 5, -1}, {0, 0, -1}},
                                                      {{0, -2, 1}, {0, 0, 1}},
                                                      {{-1, 1, 0}, {-1, 0, 0}}};

  for (const auto& [point, normal] : data) {
    CHECK(c.LocalNormalAt(point) == normal);
  }
}

SCENARIO("Intersecting a constrained cylinder") {
  const Cylinder c(1, 2);
  CHECK(c.type == Shape::Type::CYLINDER);
  CHECK(c.min == 1);
  CHECK(c.max == 2);

  const std::vector<std::tuple<Point3, Vector3, size_t>> data{
      {{0, 1.5, 0}, {0.1, 1, 0}, 0},
      {{0, 3, -5}, {0, 0, 1}, 0},
      {{0, 0, -5}, {0, 0, 1}, 0},
      {{0, 2, -5}, {0, 0, 1}, 0},
      {{0, 1, -5}, {0, 0, 1}, 0},
      {{0, 1.5, -2}, {0, 0, 1}, 2}};

  for (const auto& [origin, direction, count] : data) {
    const Ray r{origin, Normalized(direction)};
    const auto xs = c.LocalIntersect(r);
    CHECK(xs.size() == count);
  }
}

SCENARIO("The default closed value for a cylinder") {
  CHECK(Cylinder().closed == false);
}

SCENARIO("Intersecting the cpas of a closed cylinder") {
  const Cylinder c(1, 2, true);

  std::vector<std::tuple<Point3, Vector3, size_t>> data = {
      {{0, 3, 0}, {0, -1, 0}, 2},
      {{0, 3, -2}, {0, -1, 2}, 2},
      {{0, 4, -2}, {0, -1, 1}, 2},
      {{0, 0, -2}, {0, 1, 2}, 2},
      {{0, -1, -2}, {0, 1, 1}, 2}};

  for (const auto& [origin, direction, count] : data) {
    const Ray r{origin, Normalized(direction)};
    const auto xs = c.LocalIntersect(r);
    CHECK(xs.size() == 2);
  }
}

SCENARIO("The normal vector on a cylinder's end caps") {
  const Cylinder c(1, 2, true);
  const std::vector<std::tuple<Point3, Vector3>> data{{{0, 1, 0}, {0, -1, 0}},
                                                      {{0.5, 1, 0}, {0, -1, 0}},
                                                      {{0, 1, 0.5}, {0, -1, 0}},
                                                      {{0, 2, 0}, {0, 1, 0}},
                                                      {{0.5, 2, 0}, {0, 1, 0}},
                                                      {{0, 2, 0.5}, {0, 1, 0}}};

  for (const auto& [point, normal] : data) {
    CHECK(c.LocalNormalAt(point) == normal);
  }
}

}  // namespace