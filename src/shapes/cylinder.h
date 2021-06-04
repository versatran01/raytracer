#pragma once

#include "shapes/shape.h"

namespace rt {

struct CylinderBase : public Shape {
  CylinderBase(Type type, scalar min, scalar max, bool closed) noexcept
      : Shape(type), min(min), max(max), closed(closed) {}

  static bool CheckCap(const Ray& ray, scalar t, scalar cap = 1.0) noexcept {
    const auto x = ray.origin.x() + t * ray.direction.x();
    const auto z = ray.origin.z() + t * ray.direction.z();
    return (x * x + z * z) <= (cap * cap);
  }

  bool closed{false};
  scalar min{-kInf};
  scalar max{kInf};
};

struct Cylinder final : public CylinderBase {
  Cylinder(scalar min = -kInf, scalar max = kInf, bool closed = false) noexcept
      : CylinderBase(Type::CYLINDER, min, max, closed) {}

  Intersections LocalIntersect(const Ray& ray) const override;
  Vector3 LocalNormalAt(const Point3& point) const override;
  void IntersectCaps(const Ray& ray, Intersections& xs) const noexcept;
};

}  // namespace rt
