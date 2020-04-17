#include "plane.h"

#include "doctest/doctest.h"

using namespace rt;

SCENARIO("The normal of a plane is constant everywhere") {
  const Plane p;

  CHECK(p.LocalNormalAt({0, 0, 0}) == Vector3(0, 1, 0));
  CHECK(p.LocalNormalAt({10, 0, -10}) == Vector3(0, 1, 0));
  CHECK(p.LocalNormalAt({-5, 0, 150}) == Vector3(0, 1, 0));
}

SCENARIO("Intersect with a ray parallel to the plane") {
  const Plane p;
  const Ray r{Point3(0, 10, 0), Vector3(0, 0, 1)};
  const auto xs = p.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("Intersect with a coplanar ray") {
  const Plane p;
  const Ray r{Point3(0, 0, 0), Vector3(0, 0, 1)};
  const auto xs = p.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("A ray intersecting a plane from above") {
  const Plane p;
  const Ray r{Point3(0, 1, 0), Vector3(0, -1, 0)};
  const auto xs = p.LocalIntersect(r);
  CHECK(xs.size() == 1);
  CHECK(xs[0].t == 1);
}

SCENARIO("A ray intersecting a plane from below") {
  const Plane p;
  const Ray r{Point3(0, -1, 0), Vector3(0, 1, 0)};
  const auto xs = p.LocalIntersect(r);
  CHECK(xs.size() == 1);
  CHECK(xs[0].t == 1);
  CHECK(xs[0].obj->type == ShapeType::PLANE);
}