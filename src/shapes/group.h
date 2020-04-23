#pragma once

#include "shape.h"

namespace rt {

struct Group final : public Shape {
  Group() : Shape(ShapeType::GROUP) {}

  Intersections LocalIntersect(const Ray& ray) const override;

  Vector3 LocalNormalAt(const Point3& point) const override;

  template <typename T>
  T& AddChild(const T& shape) {
    auto s = std::make_shared<T>(shape);
    shapes.push_back(s);

    // need to fix parent in shape's children
    if constexpr (std::is_same_v<T, Group>) {
      for (auto& c : s->shapes) c->parent = s.get();
    }

    s->parent = this;
    return *s;
  }

  bool empty() const noexcept { return shapes.empty(); }

  std::vector<std::shared_ptr<Shape>> shapes;
};

}  // namespace rt