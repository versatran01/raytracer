#include "cube.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("A ray intersects a cube") {
  const std::vector<Point3> origins = {{5, 0.5, 0},
                                       {-5, 0.5, 0},
                                       {0.5, 5, 0},
                                       {0.5, -5, 0},
                                       {0.5, 0, 5},
                                       {0.5, 0, -5},
                                       {0, 0.5, 0}};
  const std::vector<Vector3> directions = {{-1, 0, 0},
                                           {1, 0, 0},
                                           {0, -1, 0},
                                           {0, 1, 0},
                                           {0, 0, -1},
                                           {0, 0, 1},
                                           {0, 0, 1}};
  const std::vector<std::pair<scalar, scalar>> t1t2 = {
      {4, 6}, {4, 6}, {4, 6}, {4, 6}, {4, 6}, {4, 6}, {-1, 1}};

  const Cube c;
  for (size_t i = 0; i < t1t2.size(); ++i) {
    const Ray r{origins[i], directions[i]};
    const auto xs = c.LocalIntersect(r);
    REQUIRE(xs.size() == 2);
    CHECK(xs[0].t == t1t2[i].first);
    CHECK(xs[1].t == t1t2[i].second);
  }
}

SCENARIO("A ray misses a cube") {
  const std::vector<Point3> origins = {
      {-2, 0, 0}, {0, -2, 0}, {0, 0, -2}, {2, 0, 2}, {0, 2, 2}, {2, 2, 0}};
  const std::vector<Vector3> directions = {{0.2673, 0.5345, 0.8018},
                                           {0.8018, 0.2673, 0.5345},
                                           {0.5345, 0.8018, 0.2673},
                                           {0, 0, -1},
                                           {0, -1, 0},
                                           {-1, 0, 0}};

  const Cube c;
  for (size_t i = 0; i < origins.size(); ++i) {
    const Ray r{origins[i], directions[i]};
    const auto xs = c.LocalIntersect(r);
    CHECK(xs.empty());
  }
}

SCENARIO("The normal on the surface of a cube") {
  const std::vector<Point3> points = {{1, 0.5, -0.8},
                                      {-1, -0.2, 0.9},
                                      {-0.4, 1, -0.1},
                                      {0.3, -1, -0.7},
                                      {-0.6, 0.3, 1},
                                      {0.4, 0.4, -1},
                                      {1, 1, 1},
                                      {-1, -1, -1}};
  const std::vector<Vector3> normals = {{1, 0, 0},
                                        {-1, 0, 0},
                                        {0, 1, 0},
                                        {0, -1, 0},
                                        {0, 0, 1},
                                        {0, 0, -1},
                                        {1, 0, 0},
                                        {-1, 0, 0}};

  const Cube c;
  for (size_t i = 0; i < points.size(); ++i) {
    CHECK(c.LocalNormalAt(points[i]) == normals[i]);
  }
}