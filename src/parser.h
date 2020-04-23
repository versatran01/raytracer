#pragma once

#include <iostream>

namespace rt {

struct ObjParser {
  ObjParser() = default;

  void Parse(std::istream& stream);
};

}  // namespace rt