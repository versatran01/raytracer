#include "shapes/cube.h"

namespace rt {

Intersections Cube::LocalIntersect(const Ray& ray) const {
  const auto xt = CheckAxis(ray.origin.x(), ray.direction.x());
  const auto yt = CheckAxis(ray.origin.y(), ray.direction.y());
  const auto zt = CheckAxis(ray.origin.z(), ray.direction.z());

  const auto tmin = std::max(xt(0), std::max(yt(0), zt(0)));
  const auto tmax = std::min(xt(1), std::min(yt(1), zt(1)));

  if (tmin > tmax) return {};
  return {{tmin, this}, {tmax, this}};
}

Vector3 Cube::LocalNormalAt(const Point3& point) const {
  const Point3 point_abs = point.cwiseAbs();
  const auto maxc =
      std::max(point_abs.x(), std::max(point_abs.y(), point_abs.z()));

  if (maxc == point_abs.x()) {
    return {point.x(), 0, 0};
  } else if (maxc == point_abs.y()) {
    return {0, point.y(), 0};
  } else {
    return {0, 0, point.z()};
  }
}

Array2d CheckAxis(scalar origin, scalar direction) noexcept {
  const auto tmin_num = -1 - origin;
  const auto tmax_num = 1 - origin;
  auto tmin = tmin_num / direction;
  auto tmax = tmax_num / direction;
  if (tmin > tmax) std::swap(tmin, tmax);
  return {tmin, tmax};
}

}  // namespace rt