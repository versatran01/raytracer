#include <opencv2/highgui.hpp>

#include "core/intersection.h"
#include "core/ray.h"
#include "render/canvas.h"
#include "shapes/sphere.h"

using namespace rt;

int main(int argc, char** argv) {
  const Point3 ray_origin(0, 0, -5);
  const scalar wall_z = 10;
  const scalar wall_size = 7;

  const int canvas_pixels = 512;
  const auto pixel_size = wall_size / canvas_pixels;
  const auto half_wall_size = wall_size / 2;

  Canvas canvas({canvas_pixels, canvas_pixels});
  Sphere sphere;
  // add a different material
  sphere.material.color = Color(1, 0.2, 1);

  // add a lighting source
  const PointLight light{Point3(-10, 10, -10), Color::Ones()};

  for (int y = 0; y < canvas.height(); ++y) {
    const auto world_y = half_wall_size - pixel_size * y;

    for (int x = 0; x < canvas.width(); ++x) {
      const auto world_x = -half_wall_size + pixel_size * x;

      const Point3 position(world_x, world_y, wall_z);
      const Ray ray{ray_origin, Normalized(position - ray_origin)};
      const auto xs = sphere.Intersect(ray);
      const auto hit = Hit(xs);

      if (!hit.has_value()) continue;

      const auto point = ray.Position(hit->t);
      const auto normal = sphere.NormalAt(point);
      const auto eyev = -ray.direction;
      const auto color =
          Lighting(sphere.material, sphere, light, point, eyev, normal);
      canvas.WritePixel(cv::Point{x, y}, color);
    }
  }

  cv::imshow("image", canvas.ToBgr());
  cv::waitKey(-1);
  return 0;
}