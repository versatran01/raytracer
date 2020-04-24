#include "parser.h"

#include <doctest/doctest.h>

#include <sstream>

using namespace rt;

SCENARIO("Ignoring unrecognized lines") {
  const std::string gibberish =
      "​There was a young lady named Bright​\n"
      "who traveled much faster than light.\n"
      " She set out one day​​\n"
      " in a relative way,\n"
      " and came back the previous night.​";

  std::istringstream iss(gibberish);
  Parser p;
  const auto res = p.Parse(iss);
  CHECK(res.num_lines_skipped == 5);
}

SCENARIO("Vertex records") {
  const std::string file =
      "v -1 1 0\n"
      "v -1.0000 0.5000 0.000\n"
      "v 1 0 0\n"
      "v 1 1 0\n";

  std::istringstream iss(file);
  Parser p;
  const auto res = p.Parse(iss);

  const std::vector<Point3> vertices = {
      {-1, 1, 0}, {-1, 0.5, 0}, {1, 0, 0}, {1, 1, 0}};

  REQUIRE(res.vertices.size() == 4);
  for (size_t i = 0; i < res.vertices.size(); ++i) {
    CAPTURE(i);
    CHECK(res.vertices[i] == vertices[i]);
  }
}

SCENARIO("Parsiing triangle faces") {
  const std::string file =
      "v -1 1 0\n"
      "v -1.0 0 0\n"
      "v 1 0 0\n"
      "v 1 1 0\n"
      "f 1 2 3\n"
      "f 1 3 4\n";

  std::istringstream iss(file);
  Parser p;
  const auto res = p.Parse(iss);

  const std::vector<Point3> vertices = {
      {-1, 1, 0}, {-1, 0, 0}, {1, 0, 0}, {1, 1, 0}};

  REQUIRE(res.vertices.size() == vertices.size());
  const auto& g = res.group;
  REQUIRE(g.shapes.size() == 2);

  auto t1 = static_cast<const Triangle*>(g.shapes[0].get());
  CHECK(t1->p1 == res.vertices[0]);
  CHECK(t1->p2 == res.vertices[1]);
  CHECK(t1->p3 == res.vertices[2]);

  auto t2 = static_cast<const Triangle*>(g.shapes[1].get());
  CHECK(t2->p1 == res.vertices[0]);
  CHECK(t2->p2 == res.vertices[2]);
  CHECK(t2->p3 == res.vertices[3]);
}