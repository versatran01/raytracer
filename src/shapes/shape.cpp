#include "shape.h"

#include "logging.h"
#include "sphere.h"

namespace rt {

Vector3 Shape::NormalAt(const Point3& point) const noexcept {
  const auto local_point = World2Object(point);
  const auto local_normal = LocalNormalAt(local_point);
  return Normal2World(local_normal);
  // const Transform inv = transform.inverse();
  // const Point3 local_point = inv * point;

  // call derived
  // const Vector3 local_normal = LocalNormalAt(local_point);

  // Vector3 world_normal = inv.matrix().transpose() * local_normal;
  // world_normal.w() = 0;
  // return Normalized(world_normal);
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