#include "cylinder.h"

namespace rt {

struct Cone : public CylinderBase {
  Cone(scalar min = -kInf, scalar max = kInf, bool closed = false) noexcept
      : CylinderBase(ShapeType::CONE, min, max, closed) {}

  Intersections LocalIntersect(const Ray& ray) const override final;
  Vector3 LocalNormalAt(const Point3& point) const override final;
  void IntersectCaps(const Ray& ray, Intersections& xs) const noexcept;
};

}  // namespace rt