#pragma once

#include "shape.h"

namespace rt {

struct Group : public Shape {
  bool empty() const noexcept { return shapes.empty(); }
  std::vector<std::unique_ptr<Shape>> shapes;
};

}  // namespace rt