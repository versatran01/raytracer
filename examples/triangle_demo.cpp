#include "logging.h"
#include "render.h"
#include "shapes.h"
#include "viz.h"

using namespace rt;

int main(int argc, char** argv) {
  LOG(INFO) << "Group demo";
  const Camera camera(
      {512, 512},
      kPi / 6,
      ViewTransform(Point3(0, 5, -5), Point3(0, 1, 0), Vector3(0, 1, 0)));

  const Triangle t({0, 1, 0}, {-1, 0, 0}, {1, 0, 0});

  World world;
  world.light = PointLight{Point3(-10, 10, -10), Color::Ones()};
  world.AddShape(t);

  const auto canvas = Render(camera, world, 4);
  cv::imshow("image", canvas.ToBgr());
  cv::waitKey(-1);

  return 0;
}