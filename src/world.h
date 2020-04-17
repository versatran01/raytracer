#pragma once

#include "light.h"  // PointLight
#include "shape.h"  // Shape, Intersections

namespace rt {

struct World {
  World() = default;

  template <typename T>
  void AddShape(const T& shape) noexcept {
    shapes.emplace_back(std::make_unique<T>(shape));
  }

  void set_light(const PointLight& l) noexcept { light = l; }

  Intersections Intersect(const Ray& ray) const noexcept;
  Color ColorAt(const Ray& ray, int remaining = 1) const noexcept;

  bool IsShadowed(const Point3& point) const noexcept;
  Color ShadeHit(const Computations& comps, int remaining = 1) const noexcept;
  Color Reflected(const Computations& comps, int remaining = 1) const noexcept;
  Color Refracted(const Computations& comps, int remaining = 1) const noexcept;

  bool empty() const noexcept { return shapes.empty(); }
  int size() const noexcept { return static_cast<int>(shapes.size()); }

  PointLight light;
  std::vector<std::unique_ptr<Shape>> shapes;
};

World DefaultWorld() noexcept;

}  // namespace rt
