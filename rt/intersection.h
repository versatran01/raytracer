#pragma once

#include "rt/ray.h"    // Ray
#include "rt/tuple.h"  // Point3, Vector3

namespace rt {

// fwd
struct Shape;

struct Intersection {
  Intersection() = default;
  Intersection(scalar t, const Shape* obj, scalar u, scalar v);
  Intersection(scalar t, const Shape* obj) : Intersection(t, obj, -1, -1) {}

  friend bool operator==(const Intersection& lhs,
                         const Intersection& rhs) noexcept {
    return lhs.t == rhs.t && lhs.obj == rhs.obj;
  }

  friend bool operator!=(const Intersection& lhs,
                         const Intersection& rhs) noexcept {
    return !(lhs == rhs);
  }

  scalar t;
  const Shape* obj{nullptr};
  scalar u, v;
};

using Intersections = std::vector<Intersection>;

Opt<Intersection> Hit(Intersections intersections) noexcept;

struct Computations {
  Computations(const Intersection& hit,
               const Ray& ray,
               const Intersections& inters = {}) noexcept;

  scalar Schlick() const noexcept;

  scalar t;
  const Shape* obj{nullptr};
  Point3 point;
  Vector3 eyev;
  Vector3 normal;
  Vector3 reflectv;
  bool inside;
  Point3 over_point;
  Point3 under_point;
  scalar n1;
  scalar n2;
};

std::pair<scalar, scalar> ComputeN1N2(const Intersection& hit,
                                      const Intersections& inters) noexcept;

}  // namespace rt
