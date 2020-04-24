#include "parser.h"

#include "logging.h"

namespace rt {

Parser::Result Parser::Parse(std::istream& in) const {
  Result res;
  for (std::string line; std::getline(in, line);) {
    // skip empty line
    if (line.empty()) continue;
    // Parse vertex
    if (line[0] == 'v') {
      const auto p = ParseVertex(line);
      if (p) res.vertices.push_back(*p);
    }

    // Parse triangle
    if (line[0] == 'f') {
      char c;
      int v1, v2, v3;
      std::istringstream il(line);
      if (il >> c >> v1 >> v2 >> v3) {
        LOG(INFO) << fmt::format("{} {} {}", v1, v2, v3);

        --v1;
        --v2;
        --v3;
        // Double check these indices are valid

        // build triangle
        const Triangle t(res.vertices[v1], res.vertices[v2], res.vertices[v3]);
        res.group.AddChild(t);
      } else {
        LOG(INFO) << "Failed to parse line for triangle: " << line;
      }
    }

    ++res.num_lines_skipped;
  }

  return res;
}

Opt<Point3> Parser::ParseVertex(const std::string& line) const {
  char c;
  Point3 p;
  std::istringstream il(line);
  if (il >> c >> p.x() >> p.y() >> p.z()) return p;

  // otherwise failed
  LOG(INFO) << "Failed to parse line for vertex: " << line;
  return {};
}

}  // namespace rt