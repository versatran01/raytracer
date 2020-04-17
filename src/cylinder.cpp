#include "cylinder.h"

#include "logging.h"

namespace rt {

Intersections Cylinder::LocalIntersect(const Ray& ray) const {
  const auto a = Square(ray.direction.x()) + Square(ray.direction.z());

  // ray is parallel to the y axis, but also need to check caps
  if (a < kEps) return IntersectCaps(ray);

  const auto b = 2 * ray.origin.x() * ray.direction.x() +
                 2 * ray.origin.z() * ray.direction.z();
  const auto c = Square(ray.origin.x()) + Square(ray.origin.z()) - 1;

  const auto disc = b * b - 4 * a * c;
  if (disc < 0) return {};

  const auto sqrt_disc = std::sqrt(disc);

  auto t0 = (-b - sqrt_disc) / (2 * a);
  auto t1 = (-b + sqrt_disc) / (2 * a);

  if (t0 > t1) std::swap(t0, t1);

  // truncated cylinder
  Intersections xs;
  xs.reserve(2);

  const auto y0 = ray.origin.y() + t0 * ray.direction.y();
  if (min < y0 && y0 < max) xs.emplace_back(t0, this);

  const auto y1 = ray.origin.y() + t1 * ray.direction.y();
  if (min < y1 && y1 < max) xs.emplace_back(t1, this);

  const auto xs_caps = IntersectCaps(ray);
  xs.insert(xs.end(), xs_caps.cbegin(), xs_caps.cend());

  return xs;
}

Vector3 Cylinder::LocalNormalAt(const Point3& point) const {
  // Compute the square of the distance from the y axis
  const auto dist = Square(point.x()) + Square(point.z());

  if (dist < 1 && point.y() >= (max - kEps)) {
    return {0, 1, 0};
  } else if (dist < 1 && point.y() <= (min + kEps)) {
    return {0, -1, 0};
  } else {
    return {point.x(), 0, point.z()};
  }
}

Intersections Cylinder::IntersectCaps(const Ray& ray) const noexcept {
  if (!closed || std::abs(ray.direction.y()) < kEps) return {};

  Intersections xs;
  xs.reserve(2);
  // Check for an intersection with the lower end cap by intersecting the ray
  // with the plane at y = min
  const auto tmin = (min - ray.origin.y()) / ray.direction.y();
  if (CheckCap(ray, tmin)) xs.emplace_back(tmin, this);

  const auto tmax = (max - ray.origin.y()) / ray.direction.y();
  if (CheckCap(ray, tmax)) xs.emplace_back(tmax, this);
  return xs;
}
}  // namespace rt