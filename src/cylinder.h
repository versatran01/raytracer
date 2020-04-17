#pragma once

#include "shape.h"

namespace rt {

constexpr auto inf = std::numeric_limits<scalar>::infinity();

struct Cylinder : public Shape {
  Cylinder(scalar min = -inf, scalar max = inf, bool closed = false) noexcept
      : Shape(ShapeType::CYLINDER), min(min), max(max), closed(closed) {}

  static bool CheckCap(const Ray& ray, scalar t) noexcept {
    const auto x = ray.origin.x() + t * ray.direction.x();
    const auto z = ray.origin.z() + t * ray.direction.z();
    return (x * x + z * z) <= 1;
  }

  Intersections LocalIntersect(const Ray& ray) const override final;
  Vector3 LocalNormalAt(const Point3& point) const override final;
  Intersections IntersectCaps(const Ray& ray) const noexcept;

  bool closed{false};
  scalar min{-inf};
  scalar max{inf};
};

}  // namespace rt
