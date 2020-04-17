#pragma once

#include "color.h"  // Color
#include "tuple.h"  // Point3

namespace rt {

struct PointLight {
  Point3 position;
  Color intensity;
};

}  // namespace rt