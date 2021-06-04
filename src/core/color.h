#pragma once

#include "core/types.h"  // Vector3d

namespace rt {

struct Color : public Vector3d {
  using Vector3d::Vector3d;

  auto r() const noexcept { return x(); }
  auto g() const noexcept { return y(); }
  auto b() const noexcept { return z(); }

  static Color White() noexcept { return Ones(); }
  static Color Black() noexcept { return Zero(); }

  friend Color operator*(const Color& rhs, const Color& lhs) noexcept {
    return (rhs.array() * lhs.array()).matrix();
  }
};

namespace colors {
static const Color kBlack = Color::Zero();
static const Color kWhite = Color::Ones();
}  // namespace colors

}  // namespace rt
