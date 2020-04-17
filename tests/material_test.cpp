#include "material.h"

#include <doctest/doctest.h>

#include "light.h"
#include "pattern.h"
#include "sphere.h"
#include "tuple.h"

using namespace rt;

SCENARIO("The default material") {
  const Material m;
  CHECK(m.color == Color(1, 1, 1));
  CHECK(m.ambient == 0.1);
  CHECK(m.diffuse == 0.9);
  CHECK(m.specular == 0.9);
  CHECK(m.shininess == 200.0);
}

SCENARIO("Lighting with the surface in shadow") {
  const Sphere s;
  const Material m;
  const Point3 position(0, 0, 0);
  const Vector3 eyev(0, 0, -1);
  const Vector3 normalv(0, 0, -1);
  const PointLight light{Point3(0, 0, -10), Color::Ones()};
  const auto result = Lighting(m, s, light, position, eyev, normalv, true);
  CHECK(result == Color::Constant(m.ambient));
}

TEST_CASE("Lighting test") {
  const Material m;
  const Point3 point = Point3::Zero();
  const Sphere s;

  SUBCASE("Lighting with the eye between the light and the surface") {
    const Vector3 eyev(0, 0, -1);
    const Vector3 normalv(0, 0, -1);

    const PointLight light{Point3(0, 0, -10), Color(1, 1, 1)};
    const auto result = Lighting(m, s, light, point, eyev, normalv);
    CHECK(result == Color::Constant(1.9));
  }

  SUBCASE(
      "Lighting with the eye between the light and the surface, eye offset 45 "
      "degree") {
    const Vector3 eyev(0, std::sqrt(2.0) / 2, -std::sqrt(2.0) / 2);
    const Vector3 normalv(0, 0, -1);

    const PointLight light{Point3(0, 0, -10), Color(1, 1, 1)};
    const auto result = Lighting(m, s, light, point, eyev, normalv);
    CHECK(result == Color::Ones());
  }

  SUBCASE("Lighting with the eye opposite surface light offset 45 degree") {
    const Vector3 eyev(0, 0, -1);
    const Vector3 normalv(0, 0, -1);

    const PointLight light{Point3(0, 10, -10), Color(1, 1, 1)};
    const auto result = Lighting(m, s, light, point, eyev, normalv);
    CHECK(result.isApprox(Color::Constant(0.7363961030678928)));
  }

  SUBCASE("Lighting with eye in the path of the reflection vector") {
    const Vector3 eyev(0, -std::sqrt(2.0) / 2, -std::sqrt(2.0) / 2);
    const Vector3 normalv(0, 0, -1);

    const PointLight light{Point3(0, 10, -10), Color(1, 1, 1)};
    const auto result = Lighting(m, s, light, point, eyev, normalv);
    CHECK(result.isApprox(Color::Constant(1.6363961030678928)));
  }

  SUBCASE("Lighting with the light behind the surface") {
    const Vector3 eyev(0, 0, 1);
    const Vector3 normalv(0, 0, -1);

    const PointLight light{Point3(0, 0, 10), Color(1, 1, 1)};
    const auto result = Lighting(m, s, light, point, eyev, normalv);
    CHECK(result == Color::Constant(0.1));
  }
}

SCENARIO("Lighting with a pattern applied") {
  const Sphere s;
  Material m;
  m.pattern = std::make_shared<StripePattern>(Color::White(), Color::Black());
  m.ambient = 1;
  m.diffuse = 0;
  m.specular = 0;
  const Vector3 eyev(0, 0, -1);
  const Vector3 normal(0, 0, -1);
  const PointLight light{Point3(0, 0, -10), Color::Ones()};

  const auto c1 = Lighting(m, s, light, Point3(0.9, 0, 0), eyev, normal);
  const auto c2 = Lighting(m, s, light, Point3(1.1, 0, 0), eyev, normal);

  CHECK(c1 == Color::Ones());
  CHECK(c2 == Color::Zero());
}

SCENARIO("Reflectivity for the default material") {
  const Material m;
  CHECK(m.reflective == 0.0);
}

SCENARIO("Transparency and Refractive index for the default material") {
  const Material m;
  CHECK(m.transparency == 0.0);
  CHECK(m.refractive_index == 1.0);
}