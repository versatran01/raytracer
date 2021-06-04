#include "utils/parser.h"

#include <glog/logging.h>

#include <istream>

namespace rt {

std::vector<Triangle> FanTriangulation(const std::vector<int>& indices,
                                       const std::vector<Point3>& vertices) {
  const int n_indices = indices.size();
  const int n_vertices = vertices.size();

  CHECK_GE(n_indices, 3) << "not enough indices for one triangle: "
                         << n_indices;

  std::vector<Triangle> triangles;

  const auto i1 = indices[0] - 1;
  CHECK_GE(i1, 0);
  CHECK_LT(i1, n_vertices);
  const auto& v1 = vertices[i1];

  for (int i = 1; i < n_indices - 1; ++i) {
    const auto i2 = indices[i] - 1;
    CHECK_GE(i2, 0);
    CHECK_LT(i2, n_vertices);
    const auto i3 = indices[i + 1] - 1;
    CHECK_GE(i3, 0);
    CHECK_LT(i3, n_vertices);
    triangles.emplace_back(v1, vertices[i2], vertices[i3]);
  }

  return triangles;
}

const Group* Parser::GetGroup(const std::string& name) const {
  auto it = named_groups.find(name);
  // not found
  if (it == named_groups.cend()) return nullptr;
  // found
  return &(it->second);
}

Parser Parse(std::istream& in) {
  Parser res;
  // start with default group
  Group* group = &res.default_group;
  std::string group_name;

  for (std::string line; std::getline(in, line);) {
    // skip empty line
    if (line.empty()) continue;

    std::istringstream il(line);
    std::string header;
    il >> header;

    // this is a group
    if (header == "g") {
      // Parse the group name and change current group
      il >> group_name;

      if (group_name.empty()) {
        LOG(WARNING) << "Failed to parse group name: " << line;
      } else {
        // switch current group
        group = &res.named_groups[group_name];
      }
    } else if (header == "v") {
      const auto p = ParseVertex(il);
      if (p) {
        res.vertices.push_back(*p);
      } else {
        LOG(WARNING) << "Failed to parse vertex: " << line;
      }
    } else if (header == "f") {
      std::vector<int> indices(std::istream_iterator<int>{il},
                               std::istream_iterator<int>{});
      const auto n = indices.size();

      if (n < 3) {
        LOG(WARNING) << "Failed to parse line for face: " << line;
      } else {
        const auto ts = FanTriangulation(indices, res.vertices);
        group->AddChildren(ts);
      }
    } else {
      // Not a valid line
      ++res.num_lines_skipped;
    }
  }

  return res;
}

Group Parser::ToGroup() const {
  Group group = default_group;

  for (auto& c : group.shapes) {
    c->parent = &group;
  }

  // Add named groups
  for (const auto& [k, g] : named_groups) {
    group.AddChild(g);
  }

  return group;
}

Opt<Point3> ParseVertex(std::istream& in) {
  Point3 p;
  if (in >> p.x() >> p.y() >> p.z()) return p;
  return {};
}

}  // namespace rt
