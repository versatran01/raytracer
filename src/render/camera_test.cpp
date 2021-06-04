#include "render/camera.h"

#include <doctest/doctest.h>

namespace {

using namespace rt;

SCENARIO("Constructing a camera") {
  int hsize = 160;
  int vsize = 120;
  scalar fov = kPi / 2;

  const Camera c({hsize, vsize}, fov);

  CHECK(c.width() == hsize);
  CHECK(c.height() == vsize);
  CHECK(c.fov == fov);
  CHECK(c.transform.matrix() == Transform::Identity().matrix());
}

SCENARIO("The pixel size of a horizontal canvas") {
  const Camera c({200, 125}, kPi / 2);
  CHECK(c.pixel_size == doctest::Approx(0.01));
}

SCENARIO("Constructing a ray through the center of the canvas") {
  const Camera c({200, 100}, kPi / 2);
  const auto r = c.RayAt({100, 50});
  CHECK(r.origin == Point3::Zero());
  CHECK(r.direction == Vector3(0, 0, -1));
}

SCENARIO("Constructing a ray through a corner of the canvas") {
  const Camera c({200, 100}, kPi / 2);
  const auto r = c.RayAt({0, 0});
  CHECK(r.origin == Point3::Zero());
  CHECK(r.direction.isApprox(Vector3(2.0 / 3, 1.0 / 3, -2.0 / 3)));
}

SCENARIO("Constructing a ray when the camera is tarnsformed") {
  const Camera c({200, 100},
                 kPi / 2,
                 MakeTransform(RotY(kPi / 4) * Translation3(0, -2, 5)));
  const auto r = c.RayAt({100, 50});
  CHECK(r.origin == Point3(0, 2, -5));
  CHECK(r.direction.isApprox(Vector3(kSqrt2 / 2, 0, -kSqrt2 / 2)));
}

}  // namespace