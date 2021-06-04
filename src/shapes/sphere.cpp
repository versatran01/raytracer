#include "shapes/sphere.h"

namespace rt {

Intersections Sphere::LocalIntersect(const Ray& ray) const {
  const Vector3 sphere_to_ray = ray.origin - Point3::Zero();
  const auto a = Dot(ray.direction, ray.direction);
  const auto b = Dot(ray.direction, sphere_to_ray) * 2;
  const auto c = Dot(sphere_to_ray, sphere_to_ray) - 1;
  const auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) return {};
  const auto sqrt_d = std::sqrt(discriminant);
  const auto two_a = 2 * a;
  return {{(-b - sqrt_d) / two_a, this}, {(-b + sqrt_d) / two_a, this}};
}

Sphere GlassSphere() noexcept {
  Sphere s;
  s.material.transparency = 1.0;
  s.material.refractive_index = 1.5;
  return s;
}

rt::Vector3 rt::Sphere::LocalNormalAt(const Point3& point) const {
  return point - Point3::Zero();
}

}  // namespace rt
