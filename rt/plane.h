#pragma once

#include "rt/shape.h"

namespace rt {

struct Plane final : public Shape {
  Plane() : Shape(Type::PLANE) {}

  Vector3 LocalNormalAt(const Point3& point) const override;
  Intersections LocalIntersect(const Ray& ray) const override;
};

}  // namespace rt
