#include "rt/canvas.h"

#include <doctest/doctest.h>

namespace {

using namespace rt;

SCENARIO("Creating a canvas") {
  const Canvas c({10, 20});
  CHECK(c.width() == 10);
  CHECK(c.height() == 20);

  c.image().forEach<Pixel>([&](const Pixel& pixel, const int position[]) {
    CHECK(pixel == Pixel{});
  });
}

SCENARIO("Writing pixels to a canvas") {
  Canvas c({10, 20});
  const Color red(1, 0, 0);

  c.WritePixel(Index2{2, 3}, red);
  CHECK(c.at(Index2{2, 3}) == cv::Vec3d(1, 0, 0));
  CHECK(c.at(cv::Point{3, 2}) == cv::Vec3d(1, 0, 0));
}

SCENARIO("Save canvas") {
  Canvas c({480, 320});

  for (int i = 0; i < c.height(); ++i) {
    for (int j = 0; j < c.width(); ++j) {
      c.WritePixel(Index2{i, j},
                   Color(static_cast<double>(i) / c.height(),
                         static_cast<double>(j) / c.width(),
                         0.5));
    }
  }

  CHECK(SaveCanvas(c, "/tmp/canvas.png"));
}

}  // namespace
