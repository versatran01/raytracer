#include "world.h"

#include "sphere.h"

namespace rt {

World DefaultWorld(double ambient) noexcept {
  World world;

  {
    Sphere s;
    Material& m = s.material;
    m.color = Color(0.8, 1.0, 0.6);
    m.diffuse = 0.7;
    m.specular = 0.2;
    m.ambient = ambient;
    world.AddShape(s);
  }
  {
    Sphere s;
    s.transform = Scaling3(0.5);
    s.material.ambient = ambient;
    world.AddShape(s);
  }

  world.light = {Point3(-10, 10, -10), Color::Ones()};

  return world;
}

Intersections World::Intersect(const Ray& ray) const noexcept {
  Intersections all;
  // Just be generous at reserving space to avoid repeated allocations
  all.reserve(shapes.size() * 4);
  for (const auto& shape : shapes) {
    const auto xs = shape.Intersect(ray);
    all.insert(all.end(), xs.cbegin(), xs.cend());
  }
  return all;
}

Color World::ColorAt(const Ray& ray, int remaining) const noexcept {
  const auto xs = Intersect(ray);
  const auto hit = Hit(xs);
  if (!hit.has_value()) return Color::Zero();

  const Computations comps(*hit, ray);
  return ShadeHit(comps, remaining);
}

Color World::Reflected(const Computations& comps, int remaining) const
    noexcept {
  if (remaining <= 0) return Color::Black();
  if (comps.obj->material.reflective == 0) return Color::Black();

  const Ray reflect_ray{comps.over_point, comps.reflectv};
  const auto color = ColorAt(reflect_ray, remaining - 1);
  return color * comps.obj->material.reflective;
}

Color World::Refracted(const Computations& comps, int remaining) const
    noexcept {
  if (remaining <= 0) return Color::Black();
  if (comps.obj->material.transparency == 0) return Color::Black();

  // Find the ratio of first index of refraction to the second
  const auto n_ratio = comps.n1 / comps.n2;
  // cos(theta_i) is the same as the dot product of the two vectors
  const auto cos_i = Dot(comps.eyev, comps.normal);
  // Find sin(theta)^2 via trig identity
  const auto sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
  // Total internal reflection when sin(theta)^2 > 1
  if (sin2_t > 1) return Color::Black();

  // otherwise
  // Find cos(theta_t) via trig identity
  const auto cos_t = std::sqrt(1.0 - sin2_t);
  // Compute the direction of the refracted ray
  const Vector3 direction =
      comps.normal * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;

  // Create the refracted ray
  const Ray refract_ray{comps.under_point, direction};
  // Find the color of the refracted ray, making sure to multiply by the
  // transparency value to account for any opacity
  const auto color =
      ColorAt(refract_ray, remaining - 1) * comps.obj->material.transparency;

  return color;
}

bool World::IsShadowed(const Point3& point) const noexcept {
  const Vector3 v = light.position - point;
  const auto distance = Magnitude(v);
  const Vector3 direction = Normalized(v);

  const auto xs = Intersect({point, direction});
  const auto opt_hit = Hit(xs);

  if (!opt_hit.has_value()) return false;
  // must be a hit
  return opt_hit->t < distance;
}

Color World::ShadeHit(const Computations& comps, int remaining) const noexcept {
  // NOTE: use over_point instead of point to avoid acne effect
  // Otherwise, floating point rounding errors will make some rays originate
  // just below the surface, causing them to intersect the same surface they
  // should be reflecting from.
  const auto in_shadow = IsShadowed(comps.over_point);

  const auto surface = Lighting(comps.obj->material,
                                *(comps.obj),
                                light,
                                comps.over_point,
                                comps.eyev,
                                comps.normal,
                                in_shadow);
  const auto reflected = Reflected(comps, remaining);
  const auto refracted = Refracted(comps, remaining);

  const auto& m = comps.obj->material;
  if (m.reflective > 0 && m.transparency > 0) {
    const auto reflectance = comps.Schlick();
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  }

  return surface + reflected + refracted;
}

}  // namespace rt
