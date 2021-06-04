#pragma once

#include "rt/shape.h"

namespace rt {

struct CylinderBase : public Shape {
  CylinderBase(Type type, scalar min, scalar max, bool closed)
      : Shape(type), min(min), max(max), closed(closed) {}

  static bool CheckCap(const Ray& ray, scalar t, scalar cap = 1.0);

  bool closed{false};
  scalar min{-kInf};
  scalar max{kInf};
};

struct Cylinder final : public CylinderBase {
  Cylinder(scalar min = -kInf, scalar max = kInf, bool closed = false)
      : CylinderBase(Type::CYLINDER, min, max, closed) {}

  Intersections LocalIntersect(const Ray& ray) const override;
  Vector3 LocalNormalAt(const Point3& point) const override;
  void IntersectCaps(const Ray& ray, Intersections& xs) const noexcept;
};

}  // namespace rt
