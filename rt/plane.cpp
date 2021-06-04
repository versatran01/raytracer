#include "rt/plane.h"

namespace rt {

Vector3 Plane::LocalNormalAt(const Point3& point) const { return {0, 1, 0}; }

Intersections Plane::LocalIntersect(const Ray& ray) const {
  if (std::abs(ray.direction.y()) < kEps) return {};
  const auto t = -ray.origin.y() / ray.direction.y();
  return {{t, this}};
}

}  // namespace rt
