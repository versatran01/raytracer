#include "triangle.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("Constructing a triangle") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  CHECK(t.e1 == Vector3(-1, -1, 0));
  CHECK(t.e2 == Vector3(1, -1, 0));
  CHECK(t.normal == Vector3(0, 0, -1));
}

SCENARIO("Finding the normal on a triangle") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const auto n1 = t.LocalNormalAt({0, 0.5, 0});
  const auto n2 = t.LocalNormalAt({-0.5, 0.75, 0});
  const auto n3 = t.LocalNormalAt({0.5, 0.25, 0});

  CHECK(n1 == t.normal);
  CHECK(n2 == t.normal);
  CHECK(n3 == t.normal);
}

SCENARIO("Intersecting a ray parallel to the triangle") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const Ray r{Point3(0, -1, -2), Vector3(0, 1, 0)};
  const auto xs = t.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("A ray missies the p1-p3 edge") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const Ray r{Point3(1, 1, -2), Vector3(0, 0, 1)};
  const auto xs = t.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("A ray misses the p1-p2 edge") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const Ray r{Point3(-1, 1, -2), Vector3(0, 0, 1)};
  const auto xs = t.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("A ray misses the p2-p3 edge") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const Ray r{Point3(0, -1, -2), Vector3(0, 0, 1)};
  const auto xs = t.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("A ray strikes a triangle") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const Ray r{Point3(0, 0.5, -2), Vector3(0, 0, 1)};
  const auto xs = t.LocalIntersect(r);
  REQUIRE(xs.size() == 1);
  CHECK(xs[0].t == 2);
}
