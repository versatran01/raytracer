#pragma once

#include "shape.h"

namespace rt {

struct Group : public Shape {
  Intersections LocalIntersect(const Ray& ray) const final override;

  Vector3 LocalNormalAt(const Point3& point) const final override {
    throw std::runtime_error("not implemented");
  }

  template <typename T>
  void AddChild(const T& t) {
    shapes.emplace_back(std::make_unique<T>(t));
    shapes.back()->parent = this;
  }

  bool empty() const noexcept { return shapes.empty(); }
  std::vector<std::unique_ptr<Shape>> shapes;
};

}  // namespace rt