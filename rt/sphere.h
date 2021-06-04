#pragma once

#include "rt/shape.h"

namespace rt {

struct Sphere final : public Shape {
  Sphere() noexcept : Shape(Type::SPHERE) {}

  Vector3 LocalNormalAt(const Point3& point) const override;
  Intersections LocalIntersect(const Ray& ray) const override;
};

Sphere GlassSphere() noexcept;

}  // namespace rt
