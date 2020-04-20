#include "group.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("Creating a new group") {
  const Group g;
  CHECK(g.empty());
}