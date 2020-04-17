#pragma once

#include "shape.h"

namespace rt {

struct Sphere : public Shape {
  Sphere() noexcept : Shape(ShapeType::SPHERE) {}

  Vector3 LocalNormalAt(const Point3& point) const override final {
    return point - Point3::Zero();
  }

  Intersections LocalIntersect(const Ray& ray) const override final;
};

Sphere GlassSphere() noexcept;

}  // namespace rt
