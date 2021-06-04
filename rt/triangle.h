#pragma once

#include "rt/shape.h"

namespace rt {

struct Triangle : public Shape {
  Triangle() = default;
  Triangle(const Point3& p1, const Point3& p2, const Point3& p3)
      : p1(p1),
        p2(p2),
        p3(p3),
        e1(p2 - p1),
        e2(p3 - p1),
        normal(Normalized(Cross(e2, e1))) {}

  Intersections LocalIntersect(const Ray& ray) const override;
  Vector3 LocalNormalAt(const Point3& point) const override { return normal; }

  Point3 p1, p2, p3;
  Vector3 e1, e2;
  Vector3 normal;
};

}  // namespace rt
