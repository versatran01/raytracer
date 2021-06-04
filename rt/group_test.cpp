#include "rt/group.h"

#include <doctest/doctest.h>

#include "rt/sphere.h"

namespace {

using namespace rt;

SCENARIO("Creating a new group") {
  const Group g;
  CHECK(g.empty());
}

SCENARIO("Adding a child to a group") {
  Group g;
  const Sphere s;
  g.AddChild(s);
  CHECK(!g.empty());
  CHECK(g.shapes.front()->parent->id == g.id);
}

SCENARIO("Intersecting a ray with an empty group") {
  const Group g;
  const Ray r;
  const auto xs = g.LocalIntersect(r);
  CHECK(xs.empty());
}

SCENARIO("Intersecting a ray with a nonempty group") {
  Group g;
  Sphere s1;
  Sphere s2;
  s2.transform = Translation3(0, 0, -3);
  Sphere s3;
  s3.transform = Translation3(5, 0, 0);
  g.AddChild(s1);
  g.AddChild(s2);
  g.AddChild(s3);
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  const auto xs = g.LocalIntersect(r);
  REQUIRE(xs.size() == 4);
  CHECK(xs[0].obj->id == s2.id);
  CHECK(xs[1].obj->id == s2.id);
  CHECK(xs[2].obj->id == s1.id);
  CHECK(xs[3].obj->id == s1.id);
}

SCENARIO("Intersecting a transformed group") {
  Group g;
  g.transform = Scaling3(2);
  Sphere s;
  s.transform = Translation3(5, 0, 0);
  g.AddChild(s);
  const Ray r{Point3(10, 0, -10), Vector3(0, 0, 1)};
  const auto xs = g.Intersect(r);
  CHECK(xs.size() == 2);
}

}