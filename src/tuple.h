#pragma once

#include <Eigen/StdVector>

#include "types.h"

namespace rt {

using Tuple4 = Vector4d;

// Note: inheriting from Eigen is a bad idea, but I just don't want to implement
// all those operators
struct Point3 : public Tuple4 {
  Point3() : Point3(0, 0, 0) {}
  Point3(scalar x, scalar y, scalar z) noexcept : Tuple4(x, y, z, 1.0) {}
  Point3(const ConstRef<Vector3d>& p) : Point3(p.x(), p.y(), p.z()) {}

  static Point3 Zero() noexcept { return {0, 0, 0}; }
  static Point3 Ones() noexcept { return {1, 1, 1}; }
  static Point3 Constant(scalar c) { return {c, c, c}; }

  // https://eigen.tuxfamily.org/dox/TopicCustomizing_InheritingMatrix.html
  template <typename Dervied>
  Point3(const Eigen::MatrixBase<Dervied>& other) : Tuple4(other) {}

  template <typename Derived>
  Point3& operator=(const Eigen::MatrixBase<Derived>& other) {
    Tuple4::operator=(other);
    return *this;
  }
};

struct Vector3 : public Tuple4 {
  Vector3() : Vector3(0, 0, 0) {}
  Vector3(scalar x, scalar y, scalar z) noexcept : Tuple4(x, y, z, 0.0) {}
  Vector3(const ConstRef<Vector3d>& v) : Vector3(v.x(), v.y(), v.z()) {}

  static Vector3 Constant(scalar c) { return {c, c, c}; }

  template <typename Dervied>
  Vector3(const Eigen::MatrixBase<Dervied>& other) : Tuple4(other) {}

  template <typename Derived>
  Vector3& operator=(const Eigen::MatrixBase<Derived>& other) {
    Tuple4::operator=(other);
    return *this;
  }
};

inline bool IsPoint(const Tuple4& t) { return t[3] == 1.0; }
inline bool IsVector(const Tuple4& t) { return t[3] == 0.0; }

inline scalar Magnitude(const Tuple4& t) noexcept { return t.norm(); }
inline Vector3 Normalized(const Vector3& t) noexcept { return t.normalized(); }

inline scalar Dot(const Vector3& t1, const Vector3& t2) noexcept {
  return t1.dot(t2);
}

inline Vector3 Cross(const Vector3& t1, const Vector3& t2) noexcept {
  return t1.cross3(t2);
}

inline Vector3 Reflect(const Vector3& in, const Vector3& normal) noexcept {
  return in - normal * 2 * Dot(in, normal);
}

}  // namespace rt
