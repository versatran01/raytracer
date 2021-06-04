#pragma once

#include <iosfwd>
#include <unordered_map>

#include "shapes/group.h"
#include "shapes/triangle.h"
#include "core/tuple.h"

namespace rt {

std::vector<Triangle> FanTriangulation(const std::vector<int>& indices,
                                       const std::vector<Point3>& vertices);

struct Parser {
  int num_lines_skipped{0};
  std::vector<Point3> vertices;
  Group default_group;
  std::unordered_map<std::string, Group> named_groups;

  const Group* GetGroup(const std::string& name) const;

  // Convert to group
  Group ToGroup() const;
};

Parser Parse(std::istream& in);
Opt<Point3> ParseVertex(std::istream& in);

}  // namespace rt
