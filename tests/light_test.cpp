#include "light.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("A point light has a position and intensity") {
  const Color intensity(1, 1, 1);
  const Vector3 position(0, 0, 0);

  const PointLight light{position, intensity};
  CHECK(light.position == position);
  CHECK(light.intensity == intensity);
}