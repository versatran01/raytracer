#pragma once
#include "cylinder.h"

namespace rt {

struct Cone final : public CylinderBase {
  Cone(scalar min = -kInf, scalar max = kInf, bool closed = false) noexcept
      : CylinderBase(Type::CONE, min, max, closed) {}

  Intersections LocalIntersect(const Ray& ray) const override;
  Vector3 LocalNormalAt(const Point3& point) const override;
  void IntersectCaps(const Ray& ray, Intersections& xs) const noexcept;
};

}  // namespace rt