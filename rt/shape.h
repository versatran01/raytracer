#pragma once

#include <memory>

#include "rt/intersection.h"
#include "rt/material.h"
#include "rt/transform.h"

namespace rt {

struct Shape {
  enum struct Type { BASE, SPHERE, PLANE, CUBE, CYLINDER, CONE, GROUP };

  Shape() = default;
  explicit Shape(Type type) : type(type) {}

  virtual ~Shape() = default;

  inline static int counter = 0;

  friend bool operator==(const Shape& lhs, const Shape& rhs) noexcept {
    return lhs.id == rhs.id;
  }

  Intersections Intersect(const Ray& ray) const noexcept {
    return LocalIntersect(ray.Transform(transform.inverse()));
  }

  Vector3 NormalAt(const Point3& point) const noexcept;

  Point3 World2Object(const Point3& point) const noexcept;
  Vector3 Normal2World(const Vector3& normal) const noexcept;

  virtual Intersections LocalIntersect(const Ray&) const { return {}; }
  virtual Vector3 LocalNormalAt(const Point3&) const { return {}; }

  Intersection MakeIntersection(double t) const noexcept { return {t, this}; }

  int id{counter++};
  Type type{Type::BASE};
  Material material;
  Transform transform{Transform::Identity()};
  Shape* parent{nullptr};
};

class PolyShape {
 public:
  PolyShape() = default;

  template <typename T>
  PolyShape(T x) : self_(std::make_shared<T>(std::move(x))) {}

  Intersections Intersect(const Ray& ray) const noexcept {
    return self_->Intersect(ray);
  }

  Intersection MakeIntersection(double t) const noexcept {
    return self_->MakeIntersection(t);
  }

  Vector3 NormalAt(const Point3& point) const noexcept {
    return self_->NormalAt(point);
  }

  Shape::Type type() const noexcept { return self_->type; }
  int id() const noexcept { return self_->id; }

  Material material() const noexcept { return self_->material; }

 protected:
  std::shared_ptr<const Shape> self_{nullptr};
};

}  // namespace rt
