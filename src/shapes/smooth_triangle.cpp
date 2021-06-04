#include "shapes/smooth_triangle.h"

namespace rt {

SmoothTriangle::SmoothTriangle(const Point3& p1,
                               const Point3& p2,
                               const Point3& p3,
                               const Vector3& n1,
                               const Vector3& n2,
                               const Vector3& n3)
    : Triangle(p1, p2, p3), n1(n1), n2(n2), n3(n3) {}

SmoothTriangle SmoothTriangle::Default() noexcept {
  return {{0, 1, 0}, {-1, 0, 0}, {1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {1, 0, 0}};
}

}  // namespace rt
