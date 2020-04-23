#pragma once

#include "shape.h"

namespace rt {

struct Sphere final : public Shape {
  Sphere() noexcept : Shape(ShapeType::SPHERE) {}

  Vector3 LocalNormalAt(const Point3& point) const override {
    return point - Point3::Zero();
  }

  Intersections LocalIntersect(const Ray& ray) const override;
};

Sphere GlassSphere() noexcept;

}  // namespace rt
