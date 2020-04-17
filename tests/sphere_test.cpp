#include "sphere.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("A sphere's default transformation") {
  const Sphere s;
  CHECK(s.transform.matrix() == Transform::Identity().matrix());
}

SCENARIO("Chaning a sphere's transformation") {
  Sphere s;
  s.transform = Translation3(2, 3, 4);
}

SCENARIO("The normal on a sphere at a point on the x axis") {
  const Sphere s;
  CHECK(s.NormalAt(Point3(1, 0, 0)) == Vector3(1, 0, 0));
  CHECK(s.NormalAt(Point3(0, 1, 0)) == Vector3(0, 1, 0));
  CHECK(s.NormalAt(Point3(0, 0, 1)) == Vector3(0, 0, 1));
}

SCENARIO("The normal on a sphere at a nonaxial point") {
  const Sphere s;
  CHECK(s.NormalAt(Point3::Constant(kSqrt3 / 3)) ==
        Vector3::Constant(kSqrt3 / 3));
}

SCENARIO("The normal is a normalized vector") {
  const Sphere s;
  const auto n = s.NormalAt(Point3::Constant(kSqrt3 / 3));
  CHECK(n == Normalized(n));
}

SCENARIO("Computing the normal on a translated sphere") {
  Sphere s;
  s.transform = Translation3(0, 1, 0);
  const auto n = s.NormalAt(Point3(1, 1, 0));
  CHECK(n == Vector3(1, 0, 0));
}

SCENARIO("A sphere has a default material") {
  Sphere s;
  CHECK(s.material.ambient == 0.1);
}

SCENARIO("A sphere may be assigned a material") {
  Sphere s;
  Material m;
  m.ambient = 1;
  s.material = m;
  CHECK(s.material.ambient == 1);
}

SCENARIO("A ray intersects a sphere at two points") {
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  const Sphere s;

  const auto xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t == 4.0);
  CHECK(xs[1].t == 6.0);
}

SCENARIO("A ray intersects a sphere at a tangent") {
  const Ray r{Point3(0, 1, -5), Vector3(0, 0, 1)};
  const Sphere s;

  const auto xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t == 5.0);
  CHECK(xs[1].t == 5.0);
}

SCENARIO("A ray misses a sphere") {
  const Ray r{Point3(0, 2, -5), Vector3(0, 0, 1)};
  const Sphere s;

  const auto xs = s.Intersect(r);
  CHECK(xs.size() == 0);
}

SCENARIO("A ray originates inside a sphere") {
  const Ray r{Point3(0, 0, 0), Vector3(0, 0, 1)};
  const Sphere s;

  const auto xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t == -1.0);
  CHECK(xs[1].t == 1.0);
}

SCENARIO("A sphere is behind a ray") {
  const Ray r{Point3(0, 0, 5), Vector3(0, 0, 1)};
  const Sphere s;

  const auto xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t == -6.0);
  CHECK(xs[1].t == -4.0);
}

SCENARIO("The hit, when all intersections have positive t") {
  const Sphere s;
  const auto i1 = Intersection(1, &s);
  const auto i2 = Intersection(2, &s);
  const Intersections xs{i2, i1};
  const auto i = Hit(xs);
  CHECK(i == i1);
}

SCENARIO("The hit, when some intersections have negative t") {
  const Sphere s;
  const auto i1 = Intersection(-1, &s);
  const auto i2 = Intersection(1, &s);
  const Intersections xs{i2, i1};
  const auto i = Hit(xs);
  CHECK(i == i2);
}

SCENARIO("The hit, when all intersections have negative t") {
  const Sphere s;
  const auto i1 = Intersection(-2, &s);
  const auto i2 = Intersection(-1, &s);
  const Intersections xs{i2, i1};
  const auto i = Hit(xs);
  CHECK(!i.has_value());
}

SCENARIO("The hit is always the lowest nonnegative intersection") {
  const Sphere s;
  const auto i1 = Intersection(5, &s);
  const auto i2 = Intersection(7, &s);
  const auto i3 = Intersection(-3, &s);
  const auto i4 = Intersection(2, &s);
  const Intersections xs{i1, i2, i3, i4};
  const auto i = Hit(xs);
  CHECK(i == i4);
}

SCENARIO("Intersecting a scaled sphere with a ray") {
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  Sphere s;
  s.transform = Scaling3(2, 2, 2);
  const auto xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t == 3);
  CHECK(xs[1].t == 7);
}