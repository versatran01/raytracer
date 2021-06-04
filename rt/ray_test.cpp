#include "rt/ray.h"

#include <doctest/doctest.h>

#include "rt/transform.h"

namespace {

using namespace rt;

SCENARIO("Computing a point from a distance") {
  const Ray r{Point3(2, 3, 4), Vector3(1, 0, 0)};

  CHECK(r.Position(0) == Point3(2, 3, 4));
  CHECK(r.Position(1) == Point3(3, 3, 4));
  CHECK(r.Position(-1) == Point3(1, 3, 4));
}

SCENARIO("Translating a ray") {
  const Ray r{Point3(1, 2, 3), Vector3(0, 1, 0)};

  Transform t;
  t = Translation3(3, 4, 5);
  const auto r2 = r.Transform(t);
  CHECK(r2.origin == Point3(4, 6, 8));
  CHECK(r2.direction == Vector3(0, 1, 0));
}

SCENARIO("Scaling a ray") {
  const Ray r{Point3(1, 2, 3), Vector3(0, 1, 0)};
  Transform t;
  t = Scaling3(2, 3, 4);
  const auto r2 = r.Transform(t);
  CHECK(r2.origin == Point3(2, 6, 12));
  CHECK(r2.direction == Vector3(0, 3, 0));
}

}  // namespace