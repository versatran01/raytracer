#include "group.h"

namespace rt {

Intersections Group::LocalIntersect(const Ray& ray) const {
  if (empty()) return {};

  Intersections all;
  all.reserve(shapes.size() * 4);

  for (const auto& shape : shapes) {
    const auto xs = shape->Intersect(ray);
    all.insert(all.end(), xs.cbegin(), xs.cend());
  }
  std::sort(all.begin(), all.end(), [](const auto& i1, const auto& i2) {
    return i1.t < i2.t;
  });

  return all;
}

}  // namespace rt