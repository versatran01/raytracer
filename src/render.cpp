#include "render.h"

#include "logging.h"

namespace rt {

Canvas Render(const Camera& camera,
              const World& world,
              int recursive_depth) noexcept {
  Canvas canvas(camera.size);

  for (int y = 0; y < canvas.height(); ++y) {
    for (int x = 0; x < canvas.width(); ++x) {
      const cv::Point p(x, y);
      const auto ray = camera.RayAt(p);
      const auto color = world.ColorAt(ray, recursive_depth);
      canvas.WritePixel(p, color);
    }
  }

  return canvas;
}

}  // namespace rt