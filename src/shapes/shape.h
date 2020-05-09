#pragma once

#include <memory>

#include "intersection.h"  // Intersections
#include "material.h"      // Material
#include "transform.h"     // Transform
#include "utils/te.hpp"    // te::poly, te::call

namespace rt {

namespace te = boost::te;

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
};

using ShapePoly = te::poly<IShape>;

struct Shape {
  enum struct Type { BASE, SPHERE, PLANE, CUBE, CYLINDER, CONE, GROUP };

  Shape() = default;
  Shape(Type type) : type(type) {}
  virtual ~Shape() = default;

  inline static int count = 0;

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

  int id{count++};
  Type type{Type::BASE};
  Shape* parent{nullptr};
  Material material;
  Transform transform{Transform::Identity()};
};

}  // namespace rt
