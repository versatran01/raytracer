#pragma once

#include "shapes/shape.h"

namespace rt {

struct Plane final : public Shape {
  Plane() : Shape(Type::PLANE) {}

  Vector3 LocalNormalAt(const Point3& point) const override {
    return {0, 1, 0};
  }

  Intersections LocalIntersect(const Ray& ray) const override {
    if (std::abs(ray.direction.y()) < kEps) return {};
    const auto t = -ray.origin.y() / ray.direction.y();
    return {{t, this}};
  }
};

}  // namespace rt