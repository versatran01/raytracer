#pragma once

#include <memory>  // unique_ptr

#include "rt/color.h"    // Color
#include "rt/light.h"    // PointLight
#include "rt/pattern.h"  // Pattern

namespace rt {

// fwd
struct Shape;

struct Material {
  Color color{1, 1, 1};

  scalar ambient{0.1};
  scalar diffuse{0.9};
  scalar specular{0.9};
  scalar shininess{200.0};
  scalar reflective{0.0};
  scalar transparency{0.0};
  scalar refractive_index{1.0};
  std::shared_ptr<const Pattern> pattern;
};

Color Lighting(const Material& material,
               const Shape& shape,
               const PointLight& light,
               const Point3& point,
               const Vector3& eyev,
               const Vector3& normal,
               bool in_shadow = false) noexcept;

}  // namespace rt