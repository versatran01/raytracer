#include "triangle.h"

namespace rt {

Intersections Triangle::LocalIntersect(const Ray& ray) const {
  const auto dir_cross_e2 = Cross(ray.direction, e2);
  const auto det = Dot(e1, dir_cross_e2);
  if (std::abs(det) < kEps) return {};

  // Check if ray misses by p1-p3 edge
  const auto f = 1.0 / det;
  const Vector3 p1_to_origin = ray.origin - p1;
  const auto u = f * Dot(p1_to_origin, dir_cross_e2);
  if (u < 0 || u > 1) return {};

  // Check if ray misses by p1-p2 and p2-p3 edges
  const auto origin_cross_e1 = Cross(p1_to_origin, e1);
  const auto v = f * Dot(ray.direction, origin_cross_e1);
  if (v < 0 || (u + v) > 1) return {};

  const auto t = f * Dot(e2, origin_cross_e1);
  return {{t, this, u, v}};
}

}  // namespace rt