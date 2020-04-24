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
  const auto res = Parse(iss);
  CHECK(res.num_lines_skipped == 5);
}

SCENARIO("Vertex records") {
  const std::string file =
      "v -1 1 0\n"
      "v -1.0000 0.5000 0.000\n"
      "v 1 0 0\n"
      "v 1 1 0\n";

  std::istringstream iss(file);
  const auto res = Parse(iss);

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
  const auto res = Parse(iss);

  const std::vector<Point3> vertices = {
      {-1, 1, 0}, {-1, 0, 0}, {1, 0, 0}, {1, 1, 0}};

  REQUIRE(res.vertices.size() == vertices.size());
  const auto& g = res.default_group;
  REQUIRE(g.shapes.size() == 2);

  const auto t1p = g.GetShapeAs<Triangle>(0);
  REQUIRE(t1p != nullptr);
  const auto& t1 = *t1p;
  CHECK(t1.p1 == res.vertices[0]);
  CHECK(t1.p2 == res.vertices[1]);
  CHECK(t1.p3 == res.vertices[2]);

  const auto t2p = g.GetShapeAs<Triangle>(1);
  REQUIRE(t2p != nullptr);
  const auto& t2 = *t2p;
  CHECK(t2.p1 == res.vertices[0]);
  CHECK(t2.p2 == res.vertices[2]);
  CHECK(t2.p3 == res.vertices[3]);
}

SCENARIO("Triangulating polygons") {
  const std::string file =
      "v -1 1 0\n"
      "v -1 0 0\n"
      "v 1 0 0\n"
      "v 1 1 0\n"
      "v 0 2 0\n"
      "f 1 2 3 4 5\n";

  std::istringstream iss(file);
  const auto res = Parse(iss);
  const auto& g = res.default_group;

  REQUIRE(res.vertices.size() == 5);
  REQUIRE(g.shapes.size() == 3);

  const auto t1p = g.GetShapeAs<Triangle>(0);
  REQUIRE(t1p != nullptr);
  const auto& t1 = *t1p;
  CHECK(t1.p1 == res.vertices[0]);
  CHECK(t1.p2 == res.vertices[1]);
  CHECK(t1.p3 == res.vertices[2]);

  const auto t2p = g.GetShapeAs<Triangle>(1);
  REQUIRE(t2p != nullptr);
  const auto& t2 = *t2p;
  CHECK(t2.p1 == res.vertices[0]);
  CHECK(t2.p2 == res.vertices[2]);
  CHECK(t2.p3 == res.vertices[3]);

  const auto t3p = g.GetShapeAs<Triangle>(2);
  REQUIRE(t3p != nullptr);
  const auto& t3 = *t3p;
  CHECK(t3.p1 == res.vertices[0]);
  CHECK(t3.p2 == res.vertices[3]);
  CHECK(t3.p3 == res.vertices[4]);
}

SCENARIO("Triangles in groups") {
  const std::string file =
      "v -1 1 0\n"
      "v -1 0 0\n"
      "v 1 0 0\n"
      "v 1 1 0\n"
      "v 0 2 0\n"
      "g FirstGroup\n"
      "f 1 2 3\n"
      "g SecondGroup\n"
      "f 1 3 4\n";

  std::istringstream iss(file);
  const auto res = Parse(iss);

  CHECK(res.named_groups.size() == 2);
  const auto g1 = res.GetGroup("FirstGroup");
  CHECK(g1 != nullptr);
  REQUIRE(g1->shapes.size() == 1);
  const auto g2 = res.GetGroup("SecondGroup");
  CHECK(g2 != nullptr);
  REQUIRE(g2->shapes.size() == 1);

  const auto t1 = g1->GetShapeAs<Triangle>(0);
  REQUIRE(t1);
  CHECK(t1->p1 == res.vertices[0]);
  CHECK(t1->p2 == res.vertices[1]);
  CHECK(t1->p3 == res.vertices[2]);

  const auto t2 = g2->GetShapeAs<Triangle>(0);
  REQUIRE(t2);
  CHECK(t2->p1 == res.vertices[0]);
  CHECK(t2->p2 == res.vertices[2]);
  CHECK(t2->p3 == res.vertices[3]);
}

SCENARIO("Converting an OBJ file to a group") {
  const std::string file =
      "v -1 1 0\n"
      "v -1 0 0\n"
      "v 1 0 0\n"
      "v 1 1 0\n"
      "v 0 2 0\n"
      "g FirstGroup\n"
      "f 1 2 3\n"
      "g SecondGroup\n"
      "f 1 3 4\n";

  std::istringstream iss(file);
  const auto res = Parse(iss);
  const auto group = res.ToGroup();

  REQUIRE(group.shapes.size() == 2);
  for (const auto& sub_group : group.shapes) {
    CHECK(sub_group->parent->id == group.id);
  }
}