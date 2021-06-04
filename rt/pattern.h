#pragma once

#include "rt/color.h"      // Color
#include "rt/transform.h"  // Transform
#include "rt/tuple.h"      // Point3

namespace rt {

// fwd
struct Shape;

struct Pattern {
  virtual ~Pattern() = default;
  Transform transform{Transform::Identity()};

  Color PatternAtShape(const Shape& shape, const Point3& point) const noexcept;
  virtual Color PatternAt(const Point3& point) const {
    return {point.x(), point.y(), point.z()};
  }
};

struct TwoColorPattern : public Pattern {
  TwoColorPattern() = default;
  TwoColorPattern(const Color& a, const Color& b) : a(a), b(b) {}

  Color a{Color::White()};
  Color b{Color::Black()};
};

struct StripePattern : public TwoColorPattern {
  using TwoColorPattern::TwoColorPattern;

  Color PatternAt(const Point3& point) const override final {
    if (static_cast<int>(std::floor(point.x())) % 2 == 0) return a;
    return b;
  }
};

struct GradientPattern : public TwoColorPattern {
  using TwoColorPattern::TwoColorPattern;

  Color PatternAt(const Point3& point) const override final {
    const Color distance = b - a;
    const auto fraction = point.x() - std::floor(point.x());
    return a + distance * fraction;
  }
};

struct RingPattern : public TwoColorPattern {
  using TwoColorPattern::TwoColorPattern;

  Color PatternAt(const Point3& point) const override final {
    const int f = std::floor(std::hypot(point.x(), point.z()));
    return f % 2 == 0 ? a : b;
  }
};

struct CheckerPattern : public TwoColorPattern {
  using TwoColorPattern::TwoColorPattern;

  Color PatternAt(const Point3& point) const override final {
    const int f =
        std::floor(point.x()) + std::floor(point.y()) + std::floor(point.z());
    return f % 2 == 0 ? a : b;
  }
};

}  // namespace rt
