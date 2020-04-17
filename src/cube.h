#pragma once

#include "shape.h"

namespace rt {

struct Cube : public Shape {
  Cube() noexcept : Shape(ShapeType::CUBE) {}

  Intersections LocalIntersect(const Ray& ray) const override final;
  Vector3 LocalNormalAt(const Point3& point) const override final;
};

Array2d CheckAxis(scalar origin, scalar direction) noexcept;

}  // namespace rt
