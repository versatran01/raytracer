
#include <opencv2/highgui.hpp>

#include "logging.h"
#include "render.h"
#include "shapes.h"
#include "timer.h"

using namespace rt;

int main(int argc, char** argv) {
  TimerSummary ts("render_demo");

  Plane floor;
  floor.transform = Translation3(0, 0, 0);
  floor.material.color = Color(1, 0.9, 0.9);
  floor.material.specular = 0;
  floor.material.pattern = std::make_shared<CheckerPattern>();
  floor.material.reflective = 0.1;

  Plane left_wall;
  left_wall.transform = Translation3(0, 0, 5) * RotY(-kPi / 4) * RotX(kPi / 2);
  left_wall.material = floor.material;

  Plane right_wall;
  right_wall.transform = Translation3(0, 0, 5) * RotY(kPi / 4) * RotX(kPi / 2);
  right_wall.material = floor.material;

  Sphere middle;
  middle.transform = Translation3(-0.5, 1, 0.5);
  middle.material.color = Color(0.1, 1, 0.5);
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;
  middle.material.refractive_index = 1.0;
  middle.material.reflective = 0.5;

  Cone right(-1, 0, true);
  right.transform = Translation3(1.5, 1, -0.5) * Scaling3(1.0, 2.0, 1.0);
  right.material = middle.material;
  right.material.color = Color(0.5, 1, 0.1);

  Cylinder left;
  left.min = 0;
  left.max = 1;
  left.closed = true;
  left.transform = Translation3(-1.5, 0.0, -0.75) * Scaling3(0.5);
  left.material = middle.material;
  left.material.color = Color(1, 0.8, 0.1);

  Cube cube;
  cube.transform = Translation3(0.5, 0.25, -0.5) * Scaling3(0.25);
  cube.material.color = Color(0.3, 0.4, 1.0);
  cube.material.reflective = 0.5;
  cube.material.specular = 0.4;
  cube.material.diffuse = 0.5;
  cube.material.transparency = 0;

  World world;
  world.light = PointLight{Point3(-10, 10, -10), Color::Ones()};
  world.AddShape(floor);
  world.AddShape(left_wall);
  world.AddShape(right_wall);
  world.AddShape(middle);
  world.AddShape(left);
  world.AddShape(right);
  world.AddShape(cube);

  const Camera camera(
      {1024, 512},
      kPi / 3,
      ViewTransform(Point3(0, 1.5, -5), Point3(0, 1, 0), Vector3(0, 1, 0)));

  auto t = ts.Manual("render");
  const auto canvas = Render(camera, world, 4);
  t.Stop();
  LOG(INFO) << ts.ReportAll();

  cv::imshow("image", canvas.ToBgr());
  cv::waitKey(-1);

  return 0;
}