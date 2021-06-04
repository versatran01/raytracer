#include <glog/logging.h>

#include <fstream>
#include <opencv2/highgui.hpp>

#include "render.h"
#include "shapes.h"
#include "utils/parser.h"

using namespace rt;

int main(int argc, char** argv) {
  LOG(INFO) << "Parser demo";
  const Camera camera(
      {256, 256},
      kPi / 3,
      ViewTransform(Point3(0, 5, -5), Point3(0, 1, 0), Vector3(0, 1, 0)));

  const std::string filename = "../data/teapot.obj";
  std::ifstream ifs(filename, std::ifstream::in);

  if (!ifs.good()) {
    LOG(WARNING) << "Bad file from: " << filename;
    return 0;
  }

  const auto obj = Parse(ifs).ToGroup();
  LOG(INFO) << "obj: " << obj.shapes.size();

  World world;
  world.light = PointLight{Point3(-10, 10, -10), Color::Ones()};
  world.AddShape(obj);

  const auto canvas = Render(camera, world, 2);
  cv::imshow("image", canvas.ToBgr());
  cv::waitKey(-1);

  return 0;
}