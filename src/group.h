#pragma once

#include "shape.h"

namespace rt {

struct Group : public Shape {
  Group() : Shape(ShapeType::GROUP) {}

  Intersections LocalIntersect(const Ray& ray) const override;

  Vector3 LocalNormalAt(const Point3& point) const override { return {}; }

  template <typename T>
  T& AddChild(const T& shape) {
    auto s = std::make_shared<T>(shape);
    shapes.push_back(s);
    s->parent = this;
    return *s;
  }

  bool empty() const noexcept { return shapes.empty(); }

  std::vector<std::shared_ptr<Shape>> shapes;
};

}  // namespace rt