#include "world.h"

#include <doctest/doctest.h>

#include "intersection.h"
#include "shapes.h"

using namespace rt;

SCENARIO("Creating a world") {
  const World w;
  CHECK(w.empty());
}

SCENARIO("The default world") {
  const auto w = DefaultWorld();
  CHECK(w.size() == 2);
}

SCENARIO("Intersect a world with a ray") {
  const auto w = DefaultWorld();
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  auto xs = w.Intersect(r);
  std::sort(xs.begin(), xs.end(), [](const auto& a, const auto& b) {
    return a.t < b.t;
  });

  CHECK(xs.size() == 4);
  CHECK(xs[0].t == 4);
  CHECK(xs[1].t == 4.5);
  CHECK(xs[2].t == 5.5);
  CHECK(xs[3].t == 6);
}

SCENARIO("the color when a ray misses") {
  const auto w = DefaultWorld();
  const Ray r{Point3(0, 0, -5), Vector3::UnitY()};
  CHECK(w.ColorAt(r) == Color::Zero());
}

SCENARIO("The color when a ray hits") {
  const auto w = DefaultWorld();
  const Ray r{Point3(0, 0, -5), Vector3::UnitZ()};
  CHECK((w.ColorAt(r) - Color(0.380661193081, 0.475826491351, 0.285495894811))
            .norm() < kEps);
}

// SCENARIO("The color with an intersection behind the ray") {
//   auto w = DefaultWorld();
//   auto& outer = w.shapes[0];
//   outer.material().ambient = 1;
//   auto& inner = w.shapes[1];
//   inner.material().ambient = 1;
//   const Ray r{Point3(0, 0, 0.75), -Vector3::UnitZ()};

//   CHECK(inner.type() == Shape::Type::SPHERE);
//   CHECK(outer.type() == Shape::Type::SPHERE);
//   CHECK(w.ColorAt(r) == inner.material().color);
// }

SCENARIO("There is no shadow when noting is collinear with point and light") {
  const auto w = DefaultWorld();
  const Point3 p(0, 10, 0);
  CHECK(w.IsShadowed(p) == false);
}

SCENARIO("The shadow when an object is between the point and the light") {
  const auto w = DefaultWorld();
  const Point3 p(10, -10, 10);
  CHECK(w.IsShadowed(p) == true);
}

SCENARIO("There is no shadow when an object is behind the light") {
  const auto w = DefaultWorld();
  const Point3 p(-20, 20, -20);
  CHECK(w.IsShadowed(p) == false);
}

SCENARIO("There is no shadow when an object is behind the point") {
  const auto w = DefaultWorld();
  const Point3 p(-2, 2, -2);
  CHECK(w.IsShadowed(p) == false);
}

SCENARIO("ShadeHit is given an intersection in shadow") {
  World w;
  w.light = PointLight{Point3(0, 0, -10), Color::Ones()};

  w.AddShape(Sphere());

  Sphere s;
  s.transform = Translation3(0, 0, 10);
  w.AddShape(s);
  CHECK(s.id == w.shapes.back().id());

  const Ray r{Point3(0, 0, 5), Vector3(0, 0, 1)};
  const auto i = w.shapes.back().MakeIntersection(4);
  const auto comps = Computations(i, r);
  CHECK(w.ShadeHit(comps) == Color::Constant(0.1));
}

SCENARIO("Shading an intersection") {
  const auto w = DefaultWorld();
  const Ray r{Point3(0, 0, -5), Vector3::UnitZ()};
  const auto& shape = w.shapes[0];
  const Intersection i(4, shape.get());
  const Computations comps(i, r);
  CHECK((w.ShadeHit(comps) -
         Color(0.380661193081, 0.475826491351, 0.285495894811))
            .norm() < kEps);
}

SCENARIO("Shading an intersection from the inside") {
  auto w = DefaultWorld();
  w.light = PointLight{Point3(0, 0.25, 0), Color::Ones()};
  const Ray r{Point3::Zero(), Vector3::UnitZ()};
  const auto& shape = w.shapes[1];
  const Intersection i(0.5, shape.get());
  const Computations comps(i, r);
  CHECK((w.ShadeHit(comps) - Color::Constant(0.904984472083)).norm() < kEps);
}

SCENARIO("The reflected color from a nonreflective material") {
  auto w = DefaultWorld();
  const Ray r{Point3::Zero(), Vector3::UnitZ()};
  auto* shape = w.shapes.back().get();
  shape->material.ambient = 1;
  const Intersection i(1, shape);
  const Computations comps(i, r);
  CHECK(w.Reflected(comps) == Color::Black());
}

SCENARIO("The reflected color for a reflective material") {
  auto w = DefaultWorld();
  Plane p;
  p.material.reflective = 0.5;
  p.transform = Translation3(0, -1, 0);
  w.AddShape(p);

  CHECK(w.size() == 3);
  CHECK(w.shapes.back()->material.reflective == 0.5);

  const Ray r{Point3(0, 0, -3), Vector3(0, -kSqrt2 / 2, kSqrt2 / 2)};
  const Intersection i(kSqrt2, &p);
  const Computations comps(i, r);
  CHECK((w.Reflected(comps) - Color(0.19032, 0.2379, 0.14274)).norm() < 1e-4);
}

SCENARIO("Shade hit with a reflective material") {
  auto w = DefaultWorld();
  Plane p;
  p.material.reflective = 0.5;
  p.transform = Translation3(0, -1, 0);
  w.AddShape(p);

  const Ray r{Point3(0, 0, -3), Vector3(0, -kSqrt2 / 2, kSqrt2 / 2)};
  const Intersection i(kSqrt2, &p);
  const Computations comps(i, r);
  CHECK((w.ShadeHit(comps) - Color(0.87677, 0.92436, 0.82918)).norm() < 1e-4);
}

SCENARIO("ColorAt with mutually reflective surfaces") {
  World w;
  w.light = PointLight{Point3::Zero(), Color::Ones()};
  Plane lower;
  lower.material.reflective = 1;
  lower.transform = Translation3(0, -1, 0);

  Plane upper;
  upper.material.reflective = 1;
  upper.transform = Translation3(0, 1, 0);

  w.AddShape(lower);
  w.AddShape(upper);
  CHECK(w.size() == 2);
  CHECK(w.shapes.front()->id == lower.id);

  const Ray r{Point3::Zero(), Vector3::UnitY()};
  // const auto c = w.ColorAt(r);
}

SCENARIO("The reflected color at the maximum recursive depth") {
  auto w = DefaultWorld();
  Plane p;
  p.material.reflective = 0.5;
  p.transform = Translation3(0, -1, 0);
  w.AddShape(p);

  CHECK(w.shapes.size() == 3);

  const Ray r{Point3(0, 0, -3), Vector3(0, -kSqrt2 / 2, kSqrt2 / 2)};
  const Intersection i(kSqrt2, &p);
  const Computations comps(i, r);
  CHECK(w.Reflected(comps, 0) == Color::Black());
}

SCENARIO("The refracted color with an opaque surface") {
  auto w = DefaultWorld();
  const auto* shape = w.shapes.front().get();
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  const Intersections xs{{4, shape}, {6, shape}};
  const Computations comps(xs[0], r, xs);
  CHECK(w.Refracted(comps) == Color::Black());
}

SCENARIO("There refracted color at the maximu recursive depth") {
  auto w = DefaultWorld();
  auto shape = w.shapes.front().get();
  shape->material.transparency = 1.0;
  shape->material.refractive_index = 1.5;
  const Ray r{Point3(0, 0, -5), Vector3(0, 0, 1)};
  const Intersections xs = {{4, shape}, {6, shape}};
  const Computations comps(xs[0], r, xs);
  CHECK(w.Refracted(comps, 0) == Color::Black());
}

SCENARIO("The refracted color under total internal reflection") {
  auto w = DefaultWorld();
  auto shape = w.shapes.front().get();
  shape->material.transparency = 1.0;
  shape->material.refractive_index = 1.5;
  const Ray r{Point3(0, 0, kSqrt2 / 2), Vector3(0, 1, 0)};
  const Intersections xs = {{-kSqrt2 / 2, shape}, {kSqrt2 / 2, shape}};
  // NOTE: this time you're inside the sphere, so you need to look at the second
  // intersection
  const Computations comps(xs[1], r, xs);
  CHECK(w.Refracted(comps) == Color::Black());
}

SCENARIO("The refracted color with a refracted ray") {
  auto w = DefaultWorld();
  auto A = w.shapes.front().get();
  A->material.ambient = 1.0;
  A->material.pattern = std::make_shared<Pattern>();
  auto B = w.shapes.back().get();
  B->material.transparency = 1.0;
  B->material.refractive_index = 1.5;
  const Ray r{Point3(0, 0, 0.1), Vector3(0, 1, 0)};
  const Intersections xs = {
      {-0.9899, A}, {-0.4899, B}, {0.4899, B}, {0.9899, A}};
  const Computations comps(xs[2], r, xs);
  CHECK((w.Refracted(comps) - Color(0, 0.99888, 0.04725)).norm() < 1e-4);
}

SCENARIO("ShadeHit with a transparent material") {
  auto w = DefaultWorld();
  Plane floor;
  floor.transform = Translation3(0, -1, 0);
  floor.material.transparency = 0.5;
  floor.material.refractive_index = 1.5;
  w.AddShape(floor);

  Sphere ball;
  ball.material.color = Color(1, 0, 0);
  ball.material.ambient = 0.5;
  ball.transform = Translation3(0, -3.5, -0.5);
  w.AddShape(ball);

  const Ray r{Point3(0, 0, -3), Vector3(0, -kSqrt2 / 2, kSqrt2 / 2)};
  const Intersections xs = {{kSqrt2, &floor}};
  const Computations comps(xs[0], r, xs);
  CHECK((w.ShadeHit(comps) - Color(0.93642, 0.68642, 0.68642)).norm() < 1e-4);
}

SCENARIO("ShadeHit with a reflective, transparent material") {
  auto w = DefaultWorld();
  const Ray r{Point3(0, 0, -3), Vector3(0, -kSqrt2 / 2, kSqrt2 / 2)};
  Plane floor;
  floor.transform = Translation3(0, -1, 0);
  floor.material.reflective = 0.5;
  floor.material.transparency = 0.5;
  floor.material.refractive_index = 1.5;
  w.AddShape(floor);

  Sphere ball;
  ball.material.color = Color(1, 0, 0);
  ball.material.ambient = 0.5;
  ball.transform = Translation3(0, -3.5, -0.5);
  w.AddShape(ball);
  const Intersections xs = {{kSqrt2, &floor}};
  const Computations comps(xs[0], r, xs);
  CHECK((w.ShadeHit(comps) - Color(0.93991, 0.69643, 0.69243)).norm() < 1e-2);
}