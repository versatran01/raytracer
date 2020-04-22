#include "shape.h"

#include <doctest/doctest.h>

#include "group.h"
#include "sphere.h"

using namespace rt;

SCENARIO("A shape has a parent attribute") {
  const Sphere s;
  CHECK(s.parent == nullptr);
}

SCENARIO("Converting a point from world to object space") {
  Group g1;
  g1.transform = RotY(kPi / 2);
  Group g2;
  g2.transform = Scaling3(2);
  Sphere s;
  s.transform = Translation3(5, 0, 0);

  const auto& s_ = g1.AddChild(g2).AddChild(s);
  CHECK(s_.parent->id == g2.id);
  CHECK(s_.parent->parent->id == g1.id);

  const auto p = s_.World2Object({-2, 0, -10});
  CHECK((p - Point3(0, 0, -1)).norm() < 1e-4);
}

SCENARIO("Converting a normal from object to world space") {
  Group g1;
  g1.transform = RotY(kPi / 2);
  Group g2;
  g2.transform = Scaling3(1, 2, 3);
  Sphere s;
  s.transform = Translation3(5, 0, 0);

  const auto& s_ = g1.AddChild(g2).AddChild(s);
  CHECK(s_.parent->id == g2.id);
  CHECK(s_.parent->parent->id == g1.id);

  const auto n = s_.Normal2World(Vector3::Constant(kSqrt3 / 3));
  CHECK((n - Vector3(0.2857, 0.4286, -0.8571)).norm() < 1e-4);
}