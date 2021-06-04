#include "rt/shape.h"

namespace rt {

Vector3 Shape::NormalAt(const Point3& point) const noexcept {
  const auto local_point = World2Object(point);
  const auto local_normal = LocalNormalAt(local_point);
  return Normal2World(local_normal);
}

Point3 Shape::World2Object(const Point3& point) const noexcept {
  return transform.inverse() *
         (parent == nullptr ? point : parent->World2Object(point));
}

Vector3 Shape::Normal2World(const Vector3& normal) const noexcept {
  Vector3 n = transform.inverse().matrix().transpose() * normal;
  n.w() = 0;
  n = Normalized(n);

  if (parent) n = parent->Normal2World(n);
  return n;
}

}  // namespace rt