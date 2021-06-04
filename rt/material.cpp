#include "rt/material.h"

namespace rt {

Color Lighting(const Material& material,
               const Shape& shape,
               const PointLight& light,
               const Point3& point,
               const Vector3& eyev,
               const Vector3& normal,
               bool in_shadow) noexcept {
  // combine the surface color with the light's color/intensity
  const auto& material_color =
      material.pattern ? material.pattern->PatternAtShape(shape, point)
                       : material.color;
  const Color effective_color = material_color * light.intensity;

  // find the direction to the light source
  const Vector3 lightv = Normalized(light.position - point);

  // compute the ambient contribution
  const Color ambient = effective_color * material.ambient;

  // light_dot_normal represents the cosine of the angle between the light
  // vector and the normal vector
  // A negative number means the light is on the other side of the surface.
  const auto light_dot_normal = Dot(lightv, normal);
  // Ignores the specular and diffuse components when point is in shadow
  if (light_dot_normal < 0 || in_shadow) return ambient;

  // compute the diffuse contribution
  const Color diffuse = effective_color * material.diffuse * light_dot_normal;
  // reflect_dot_eye represents the cosine of the angle between the reflection
  // vector and the eye vector.
  // A negative number means the light reflects away from the eye
  const Vector3 reflectv = Reflect(-lightv, normal);
  const auto reflect_dot_eye = Dot(reflectv, eyev);
  if (reflect_dot_eye <= 0) return ambient + diffuse;

  // compute the specular contribution
  const auto factor = std::pow(reflect_dot_eye, material.shininess);
  const Color specular = light.intensity * material.specular * factor;
  return ambient + diffuse + specular;
}

}  // namespace rt