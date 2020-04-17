#pragma once

#include <memory>

#include "intersection.h"  // Intersections
#include "material.h"      // Material
#include "transform.h"     // Transform

namespace rt {

enum struct ShapeType { BASE, SPHERE, PLANE, CUBE, CYLINDER };

struct Shape {
  Shape() = default;
  Shape(ShapeType type) : type(type) {}
  virtual ~Shape() = default;

  inline static int count = 0;

  friend bool operator==(const Shape& lhs, const Shape& rhs) noexcept {
    return lhs.id == rhs.id;
  }

  Intersections Intersect(const Ray& ray) const noexcept {
    return LocalIntersect(ray.Transform(transform.inverse()));
  }

  Vector3 NormalAt(const Point3& point) const noexcept;

  virtual Intersections LocalIntersect(const Ray& ray) const = 0;
  virtual Vector3 LocalNormalAt(const Point3& point) const = 0;

  const int id{count++};
  Material material;
  Transform transform{Transform::Identity()};
  ShapeType type{ShapeType::BASE};
};

}  // namespace rt