#include "canvas.h"
#include "intersection.h"
#include "logging.h"
#include "ray.h"
#include "sphere.h"
#include "viz.h"

using namespace rt;

int main(int argc, char** argv) {
  const Point3 ray_origin(0, 0, -5);
  const scalar wall_z = 10;
  const scalar wall_size = 7;

  const int canvas_pixels = 256;
  const auto pixel_size = wall_size / canvas_pixels;
  const auto half_wall_size = wall_size / 2;

  Canvas canvas({canvas_pixels, canvas_pixels});
  const Color color(1, 0, 0);
  Sphere s;
  s.transform = Scaling3(1, 0.5, 1);

  for (int y = 0; y < canvas.height(); ++y) {
    const auto world_y = -half_wall_size + pixel_size * y;

    for (int x = 0; x < canvas.width(); ++x) {
      const auto world_x = -half_wall_size + pixel_size * x;

      const Point3 position(world_x, world_y, wall_z);
      const Ray r{ray_origin, Normalized(position - ray_origin)};
      const auto xs = s.Intersect(r);
      const auto hit = Hit(xs);

      if (hit.has_value()) {
        canvas.WritePixel(cv::Point{x, y}, color);
      }
    }
  }

  cv::imshow("image", canvas.ToBgr());
  cv::waitKey(-1);
}