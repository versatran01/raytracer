#pragma once

#include "triangle.h"

namespace rt {

struct SmoothTriangle final : public Triangle {
  SmoothTriangle() = default;
  SmoothTriangle(const Point3& p1,
                 const Point3& p2,
                 const Point3& p3,
                 const Vector3& n1,
                 const Vector3& n2,
                 const Vector3& n3)
      : Triangle(p1, p2, p3), n1(n1), n2(n2), n3(n3) {}

  static SmoothTriangle Default() noexcept {
    return {{0, 1, 0}, {-1, 0, 0}, {1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {1, 0, 0}};
  }

  Vector3 LocalNormalAt(const Point3& point) const override { return {}; }

  Vector3 n1, n2, n3;
};

}  // namespace rt
