#pragma once
#include "transform.h"  // Transform
#include "tuple.h"      // Point3, Vector3

namespace rt {

struct Ray {
  Point3 origin;
  Vector3 direction;

  Point3 Position(scalar t) const noexcept { return origin + direction * t; }

  Ray Transform(const Transform& transform) const noexcept {
    return {Point3{transform * origin}, Vector3{transform * direction}};
  }
};

}  // namespace rt