#pragma once

#include "rt/color.h"
#include "rt/tuple.h"

namespace rt {

struct PointLight {
  Point3 position;
  Color intensity;
};

}  // namespace rt