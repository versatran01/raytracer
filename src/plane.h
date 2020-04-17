#pragma once

#include "shape.h"  // Shape

namespace rt {

struct Plane : public Shape {
  Plane() : Shape(ShapeType::PLANE) {}

  Vector3 LocalNormalAt(const Point3& point) const override final {
    return {0, 1, 0};
  }

  Intersections LocalIntersect(const Ray& ray) const override final {
    if (std::abs(ray.direction.y()) < kEps) return {};
    const auto t = -ray.origin.y() / ray.direction.y();
    return {{t, this}};
  }
};

}  // namespace rt