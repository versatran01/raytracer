#include "rt/cone.h"

namespace rt {

Cone::Cone(scalar min, scalar max, bool closed) noexcept
    : CylinderBase(Type::CONE, min, max, closed) {}

Intersections Cone::LocalIntersect(const Ray& ray) const {
  const auto a = Square(ray.direction.x()) - Square(ray.direction.y()) +
                 Square(ray.direction.z());

  const auto b = 2 * (ray.origin.x() * ray.direction.x() -
                      ray.origin.y() * ray.direction.y() +
                      ray.origin.z() * ray.direction.z());

  const auto c =
      Square(ray.origin.x()) - Square(ray.origin.y()) + Square(ray.origin.z());

  Intersections xs;
  xs.reserve(4);

  // a is zero
  if (std::abs(a) < kEps) {
    // the ray will miss when both a and b are zero
    if (std::abs(b) > kEps) {
      // if b is not zero
      const auto t = -c / (2 * b);
      xs.emplace_back(t, this);
    }
  }

  const auto disc = b * b - 4 * a * c;
  if (disc >= 0) {
    const auto sqrt_disc = std::sqrt(disc);

    auto t0 = (-b - sqrt_disc) / (2 * a);
    auto t1 = (-b + sqrt_disc) / (2 * a);

    if (t0 > t1) std::swap(t0, t1);

    // truncated cone
    const auto y0 = ray.origin.y() + t0 * ray.direction.y();
    if (min < y0 && y0 < max) xs.emplace_back(t0, this);

    const auto y1 = ray.origin.y() + t1 * ray.direction.y();
    if (min < y1 && y1 < max) xs.emplace_back(t1, this);
  }

  IntersectCaps(ray, xs);
  return xs;
}

Vector3 Cone::LocalNormalAt(const Point3& point) const {
  // Compute the square of the distance from the y axis
  const auto dist_sq = Square(point.x()) + Square(point.z());

  if (dist_sq < 1 && point.y() >= (max - kEps)) {
    return {0, 1, 0};
  } else if (dist_sq < 1 && point.y() <= (min + kEps)) {
    return {0, -1, 0};
  } else {
    auto y = std::sqrt(dist_sq);
    if (point.y() > 0) y = -y;
    return {point.x(), y, point.z()};
  }
}

void Cone::IntersectCaps(const Ray& ray, Intersections& xs) const noexcept {
  if (!closed || std::abs(ray.direction.y()) < kEps) return;

  // Check for an intersection with the lower end cap by intersecting the ray
  // with the plane at y = min
  const auto tmin = (min - ray.origin.y()) / ray.direction.y();
  if (CheckCap(ray, tmin, min)) xs.emplace_back(tmin, this);

  const auto tmax = (max - ray.origin.y()) / ray.direction.y();
  if (CheckCap(ray, tmax, max)) xs.emplace_back(tmax, this);
}

}  // namespace rt
