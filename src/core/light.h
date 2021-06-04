#pragma once

#include "core/color.h"
#include "core/tuple.h"

namespace rt {

struct PointLight {
  Point3 position;
  Color intensity;
};

}  // namespace rt