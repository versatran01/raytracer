#pragma once

#include <memory>

#include "intersection.h"  // Intersections
#include "material.h"      // Material
#include "transform.h"     // Transform
#include "utils/te.hpp"    // te::poly, te::call

namespace rt {

namespace te = boost::te;

struct Shape {
  enum struct Type { BASE, SPHERE, PLANE, CUBE, CYLINDER, CONE, GROUP };

  Shape() = default;
  Shape(Type type) : type(type) {}
  virtual ~Shape() = default;

  inline static int counter = 0;

  friend bool operator==(const Shape& lhs, const Shape& rhs) noexcept {
    return lhs.id == rhs.id;
  }

  Intersections Intersect(const Ray& ray) const noexcept {
    return LocalIntersect(ray.Transform(transform.inverse()));
  }

  Vector3 NormalAt(const Point3& point) const noexcept;

  Point3 World2Object(const Point3& point) const noexcept;
  Vector3 Normal2World(const Vector3& normal) const noexcept;

  virtual Intersections LocalIntersect(const Ray&) const { return {}; }
  virtual Vector3 LocalNormalAt(const Point3&) const { return {}; }

  Intersection MakeIntersection(double t) const noexcept { return {t, this}; }

  int id{counter++};
  Type type{Type::BASE};
  Material material;
  Transform transform{Transform::Identity()};
  Shape* parent{nullptr};
};

struct IShape {
  Intersections Intersect(const Ray& ray) const noexcept {
    return te::call<Intersections>(
        [](auto const& self, const Ray& ray) { return self.Intersect(ray); },
        *this,
        ray);
  }

  Vector3 NormalAt(const Point3& point) const noexcept {
    return te::call<Vector3>(
        [](const auto& self, const Point3& point) {
          return self.NormalAt(point);
        },
        *this,
        point);
  }

  Shape::Type type() const noexcept {
    return te::call<Shape::Type>([](const auto& self) { return self.type; },
                                 *this);
  }

  int id() const noexcept {
    return te::call<int>([](const auto& self) { return self.id; }, *this);
  }

  Intersection MakeIntersection(double t) const noexcept {
    return te::call<Intersection>(
        [](const auto& self, double t) { return self.MakeIntersection(t); },
        *this,
        t);
  }
};

using PolyShape = te::poly<IShape>;

}  // namespace rt
