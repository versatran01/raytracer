#include <glog/logging.h>

#include <opencv2/highgui.hpp>

#include "render.h"
#include "shapes.h"

using namespace rt;

Sphere HexagonCorner() {
  Sphere s;
  s.transform = Translation3(0, 0, -1) * Scaling3(0.25);
  return s;
}

Cylinder HexagonEdge() {
  Cylinder c(0, 1);
  c.transform = Translation3(0, 0, -1) * RotY(-kPi / 6) * RotZ(-kPi / 2) *
                Scaling3(0.25, 1, 0.25);
  return c;
}

Group HexagonSide() {
  Group g;
  g.AddChild(HexagonCorner());
  g.AddChild(HexagonEdge());
  return g;
}

Group Hexagon() {
  Group h;
  for (int i = 0; i < 6; ++i) {
    auto side = HexagonSide();
    side.transform = RotY(i * kPi / 3);
    h.AddChild(side);
  }
  h.transform = Translation3(0, 1, 0);
  return h;
}

int main(int argc, char** argv) {
  LOG(INFO) << "Group demo";
  const Camera camera(
      {512, 512},
      kPi / 6,
      ViewTransform(Point3(0, 5, -5), Point3(0, 1, 0), Vector3(0, 1, 0)));

  World world;
  world.light = PointLight{Point3(-10, 10, -10), Color::Ones()};
  world.AddShape(Hexagon());

  const auto canvas = Render(camera, world, 4);
  cv::imshow("image", canvas.ToBgr());
  cv::waitKey(-1);

  return 0;
}