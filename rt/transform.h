#pragma once

#include "tuple.h"
#include "types.h"

namespace rt {

using Transform = Eigen::Transform<scalar, 3, Eigen::Affine>;
using Translation3 = Eigen::Translation3d;
using AngleAxis = Eigen::AngleAxisd;

inline auto Scaling3(scalar x, scalar y, scalar z) noexcept {
  return Eigen::Scaling(x, y, z);
}
inline auto Scaling3(scalar s) noexcept { return Scaling3(s, s, s); }

inline AngleAxis RotX(scalar rad) noexcept { return {rad, Vector3d(1, 0, 0)}; }
inline AngleAxis RotY(scalar rad) noexcept { return {rad, Vector3d(0, 1, 0)}; }
inline AngleAxis RotZ(scalar rad) noexcept { return {rad, Vector3d(0, 0, 1)}; }

inline Matrix3d Shearing3(
    scalar xy, scalar xz, scalar yx, scalar yz, scalar zx, scalar zy) noexcept {
  Matrix3d s = Matrix3d::Identity();
  s(0, 1) = xy;
  s(0, 2) = xz;
  s(1, 0) = yx;
  s(1, 2) = yz;
  s(2, 0) = zx;
  s(2, 1) = zy;
  return s;
}

inline Transform ViewTransform(const Point3& from,
                               const Point3& to,
                               const Vector3& up) noexcept {
  const Vector3 forward = Normalized(to - from);
  const Vector3 upn = Normalized(up);
  const Vector3 left = Cross(forward, upn);
  const Vector3 true_up = Cross(left, forward);

  Matrix3d orientation;
  orientation.row(0) = left.head<3>();
  orientation.row(1) = true_up.head<3>();
  orientation.row(2) = -forward.head<3>();

  Transform t;
  t = orientation * Translation3(-from.head<3>());
  return t;
}

template <typename T>
Transform MakeTransform(T&& t) noexcept {
  Transform tf;
  tf = t;
  return tf;
}

}  // namespace rt