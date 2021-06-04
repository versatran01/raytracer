#include "intersection.h"

#include "shapes/shapes.h"

namespace rt {

Opt<Intersection> Hit(Intersections intersections) noexcept {
  std::sort(intersections.begin(),
            intersections.end(),
            [](const auto& i1, const auto& i2) { return i1.t < i2.t; });
  for (const auto& intersection : intersections) {
    if (intersection.t >= 0) return intersection;
  }
  return {};
}

Computations::Computations(const Intersection& hit,
                           const Ray& ray,
                           const Intersections& inters) noexcept
    : t(hit.t),
      obj(hit.obj),
      point(ray.Position(t)),
      eyev(-ray.direction),
      normal(obj->NormalAt(point)) {
  if (Dot(normal, eyev) < 0) {
    inside = true;
    normal = -normal;
  } else {
    inside = false;
  }

  over_point = point + normal * kEps;
  under_point = point - normal * kEps;
  reflectv = Reflect(ray.direction, normal);

  const auto n1n2 = ComputeN1N2(hit, inters);
  n1 = n1n2.first;
  n2 = n1n2.second;
}

std::pair<scalar, scalar> ComputeN1N2(const Intersection& hit,
                                      const Intersections& inters) noexcept {
  // Refraction
  std::vector<const Shape*> shapes;
  std::pair<scalar, scalar> n1n2{1.0, 1.0};

  for (const auto& inter : inters) {
    if (inter == hit) {
      n1n2.first =
          shapes.empty() ? 1.0 : shapes.back()->material.refractive_index;
    }

    // check if inter.obj is in container
    const auto it = std::find_if(
        shapes.cbegin(), shapes.cend(), [&inter](const Shape* shape) {
          return *shape == *(inter.obj);
        });

    if (it == shapes.cend()) {
      // not found, add inter.obj to shapes
      shapes.push_back(inter.obj);
    } else {
      // found, remove inter.obj from containers
      shapes.erase(it);
    }

    if (inter == hit) {
      n1n2.second =
          shapes.empty() ? 1.0 : shapes.back()->material.refractive_index;
      break;  // no need to search further
    }
  }

  return n1n2;
}

scalar Computations::Schlick() const noexcept {
  // find the cosine of the angle between the eye and normal vectors
  auto cos = Dot(eyev, normal);
  // Total internal reflection can only occur if n1 > n2
  if (n1 > n2) {
    const auto n = n1 / n2;
    const auto sin2_t = n * n * (1.0 - cos * cos);
    if (sin2_t > 0) return 1.0;
    // compute cosine of theta_t using trig identity
    const auto cos_t = std::sqrt(1.0 - sin2_t);
    // When n1 > n2, use cos(theta_t) instead
    cos = cos_t;
  }

  // n1 <= n2
  auto r0 = std::pow((n1 - n2) / (n1 + n2), 2);
  return r0 + (1 - r0) * std::pow(1 - cos, 5);
}

Intersection::Intersection(scalar t, const Shape* obj, scalar u, scalar v)
    : t(t), obj(obj), u(u), v(v) {}

}  // namespace rt
