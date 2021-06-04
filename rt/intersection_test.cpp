#include "rt/intersection.h"

#include <doctest/doctest.h>

#include "rt/shapes.h"

namespace {

using namespace rt;

SCENARIO("Precomputing the state of an intersection") {
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  const Sphere s;
  const auto i = Intersection(4, &s);
  const Computations data(i, r);

  CHECK(data.t == i.t);
  CHECK(data.obj == &s);
  CHECK(data.point == Point3(0, 0, -1));
  CHECK(data.eyev == Vector3(0, 0, -1));
  CHECK(data.normal == Vector3(0, 0, -1));
}

SCENARIO("The hit, when an intersection occurs on the outside") {
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  const Sphere s;
  const auto i = Intersection(4, &s);
  const Computations data(i, r);

  CHECK(!data.inside);
}

SCENARIO("The hit, when an intersection occurs on the inside") {
  const Ray r{Point3(0, 0, 0), Vector3(0, 0, 1)};
  const Sphere s;
  const auto i = Intersection(1, &s);
  const Computations data(i, r);

  CHECK(data.inside);
  CHECK(data.point == Point3(0, 0, 1));
  CHECK(data.eyev == Vector3(0, 0, -1));
  CHECK(data.normal == Vector3(0, 0, -1));
}

SCENARIO("The hit should offset the point") {
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  Sphere s;
  s.transform = Translation3(0, 0, 1);
  const Intersection i(5, &s);
  const Computations comps(i, r);
  CHECK(comps.over_point.z() < -kEps / 2);
  CHECK(comps.point.z() > comps.over_point.z());
}

SCENARIO("Precomputing the reflection vector") {
  const Plane p;
  const Ray r{Point3(0, 1, -1), Vector3(0, -kSqrt2 / 2, kSqrt2 / 2)};
  const Intersection i(kSqrt2, &p);
  const Computations comps(i, r);
  CHECK(comps.reflectv == Vector3(0, kSqrt2 / 2, kSqrt2 / 2));
}

TEST_CASE("Finding n1 and n2 at various intersections") {
  auto A = GlassSphere();
  A.transform = Scaling3(2);
  A.material.refractive_index = 1.5;

  auto B = GlassSphere();
  B.transform = Translation3(0, 0, -0.25);
  B.material.refractive_index = 2.0;

  auto C = GlassSphere();
  C.transform = Translation3(0, 0, 0.25);
  C.material.refractive_index = 2.5;

  const Ray r{Point3(0, 0, -4), Vector3(0, 0, 1)};
  const Intersections xs{
      {2, &A}, {2.75, &B}, {3.25, &C}, {4.75, &B}, {5.25, &C}, {6, &A}};

  std::vector<std::pair<scalar, scalar>> n1n2{
      {1.0, 1.5}, {1.5, 2.0}, {2.0, 2.5}, {2.5, 2.5}, {2.5, 1.5}, {1.5, 1.0}};

  for (int i = 0; i < xs.size(); ++i) {
    const Computations comps(xs[i], r, xs);
    CHECK(comps.n1 == n1n2[i].first);
    CHECK(comps.n2 == n1n2[i].second);
  }
}

SCENARIO("The udner point is offset below the surface") {
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  auto s = GlassSphere();
  s.transform = Translation3(0, 0, 1);
  const Intersection i(5, &s);
  const Intersections xs = {i};
  const Computations comps(i, r, xs);

  CHECK(comps.under_point.z() > kEps / 2);
  CHECK(comps.point.z() < comps.under_point.z());
}

SCENARIO("The Schlick approximation udner total internal reflection") {
  const auto shape = GlassSphere();
  const Ray r{Point3(0, 0, kSqrt2 / 2), Vector3(0, 1, 0)};
  const Intersections xs = {{-kSqrt2 / 2, &shape}, {kSqrt2, &shape}};
  const Computations comps(xs[1], r, xs);
  CHECK(comps.Schlick() == 1.0);
}

SCENARIO("The Schlick approximation with a perpendicular viewing angle") {
  const auto shape = GlassSphere();
  const Ray r{Point3(0, 0, 0), Vector3(0, 1, 0)};
  const Intersections xs = {{-1, &shape}, {1, &shape}};
  const Computations comps(xs[1], r, xs);
  CHECK(comps.Schlick() == doctest::Approx(0.04));
}

SCENARIO("The Schlick approximation with small angle n2 > n1") {
  const auto shape = GlassSphere();
  const Ray r{Point3(0, 0.99, -2), Vector3(0, 0, 1)};
  const Intersections xs = {{1.8589, &shape}};
  const Computations comps(xs[0], r, xs);
  CHECK(comps.Schlick() == doctest::Approx(0.48873));
}

SCENARIO("An intersection with u and v") {
  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});
  const Intersection i(3.5, &t, 0.2, 0.4);
  CHECK(i.u == 0.2);
  CHECK(i.v == 0.4);
}

}