#pragma once

#include "rt/light.h"  // PointLight
#include "rt/ray.h"
#include "rt/shape.h"  // Shape, Intersections

namespace rt {

struct World {
  World() = default;

  void AddShape(const PolyShape& shape) { shapes.push_back(shape); }

  void set_light(const PointLight& l) { light = l; }

  Intersections Intersect(const Ray& ray) const noexcept;
  Color ColorAt(const Ray& ray, int remaining = 1) const noexcept;

  bool IsShadowed(const Point3& point) const noexcept;
  Color ShadeHit(const Computations& comps, int remaining = 1) const noexcept;
  Color Reflected(const Computations& comps, int remaining = 1) const noexcept;
  Color Refracted(const Computations& comps, int remaining = 1) const noexcept;

  bool empty() const noexcept { return shapes.empty(); }
  int size() const noexcept { return static_cast<int>(shapes.size()); }

  PointLight light;
  std::vector<PolyShape> shapes;
};

World DefaultWorld(double ambient = 0.1) noexcept;

}  // namespace rt
