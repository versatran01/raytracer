#pragma once

#include "shape.h"

namespace rt {

struct Cube final : public Shape {
  Cube() noexcept : Shape(ShapeType::CUBE) {}

  Intersections LocalIntersect(const Ray& ray) const override;
  Vector3 LocalNormalAt(const Point3& point) const override;
};

Array2d CheckAxis(scalar origin, scalar direction) noexcept;

}  // namespace rt
