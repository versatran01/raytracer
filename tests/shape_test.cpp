#include "shape.h"

#include <doctest/doctest.h>

#include "sphere.h"

using namespace rt;

SCENARIO("A shape has a parent attribute") {
  const Sphere s;
  CHECK(s.parent == nullptr);
}
