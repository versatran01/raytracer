#include "pattern.h"

#include "shape.h"

namespace rt {

Color Pattern::PatternAtShape(const Shape& shape, const Point3& point) const
    noexcept {
  const auto object_point = shape.World2Object(point);
  // const Point3 object_point = shape.transform.inverse() * point;
  const Point3 pattern_point = transform.inverse() * object_point;
  return PatternAt(pattern_point);
}

}  // namespace rt