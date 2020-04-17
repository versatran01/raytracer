#include "shape.h"

#include "sphere.h"

namespace rt {

Vector3 Shape::NormalAt(const Point3& point) const noexcept {
  const Transform inv = transform.inverse();
  const Point3 local_point = inv * point;

  // call derived
  const Vector3 local_normal = LocalNormalAt(local_point);

  Vector3 world_normal = inv.matrix().transpose() * local_normal;
  world_normal.w() = 0;
  return Normalized(world_normal);
}

}  // namespace rt