#pragma once

#include <istream>

#include "group.h"
#include "triangle.h"
#include "tuple.h"

namespace rt {

struct Parser {
  struct Result {
    int num_lines_skipped{0};
    std::vector<Point3> vertices;
    Group group;
  };

  Opt<Point3> ParseVertex(const std::string& line) const;

  Result Parse(std::istream& stream) const;
};

}  // namespace rt