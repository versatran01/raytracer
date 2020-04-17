#include "render.h"

#include <doctest/doctest.h>

using namespace rt;

SCENARIO("Rendering a world with a camera") {
  const auto w = DefaultWorld();
  const auto t =
      ViewTransform(Point3(0, 0, -5), Point3::Zero(), Vector3::UnitY());
  const auto c = Camera({10, 10}, kPi / 2, t);
  const auto image = Render(c, w);
  const auto v = image.color_at(cv::Point{5, 5});
  CHECK((v - Color(0.380661193081, 0.475826491351, 0.285495894811)).norm() <
        kEps);
}