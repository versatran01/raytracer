#pragma once

#include <absl/container/inlined_vector.h>
#include <absl/types/optional.h>
#include <absl/types/span.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

namespace rt {

using Array2d = Eigen::Array2d;
using Array3d = Eigen::Array3d;
using Vector2d = Eigen::Vector2d;
using Vector3d = Eigen::Vector3d;
using Vector4d = Eigen::Vector4d;
using Matrix4d = Eigen::Matrix4d;
using Matrix3d = Eigen::Matrix3d;

using scalar = double;

template <typename T>
using Span = absl::Span<T>;

template <typename T>
using ConstSpan = absl::Span<const T>;

template <typename T>
using Opt = absl::optional<T>;

template <typename T>
using Ref = Eigen::Ref<T>;

template <typename T>
using ConstRef = Eigen::Ref<const T>;

constexpr scalar kPi = M_PI;
constexpr scalar kSqrt2 = std::sqrt(2.0);
constexpr scalar kSqrt3 = std::sqrt(3.0);
constexpr scalar kEps = 1e-6;
constexpr auto kInf = std::numeric_limits<scalar>::infinity();

template <typename T>
T Square(T x) noexcept {
  return x * x;
}

}  // namespace rt