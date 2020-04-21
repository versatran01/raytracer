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
  MESSAGE(g1.id);
  Group g2;
  g2.transform = Scaling3(2);
  MESSAGE(g2.id);
  Sphere s;
  s.transform = Translation3(5, 0, 0);
  MESSAGE(s.id);

  g2.AddChild(s);
  g1.AddChild(g2);
  CHECK(g2.shapes[0]->parent->id == g2.id);
  CHECK(g1.shapes[0]->parent->id == g1.id);
  CHECK(g2.shapes[0]->parent->parent->id == g1.id);

  const auto p = g2.shapes[0]->World2Object({-2, 0, -10});
  CHECK(p == Point3(0, 0, -1));
}

SCENARIO("Converting a normal from object to world space") {
  Group g1;
  g1.transform = RotY(kPi / 2);
  Group g2;
  g2.transform = Scaling3(1, 2, 3);
  Sphere s;
  s.transform = Translation3(5, 0, 0);

  g2.AddChild(s);
  g1.AddChild(g2);

  const auto n = g2.shapes[0]->Normal2World(Vector3::Constant(kSqrt3 / 3));
  CHECK(n == Vector3(0.2857, 0.4286, -0.8571));
}