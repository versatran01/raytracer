#include "render/render.h"

#include <tbb/parallel_for.h>

namespace rt {

Canvas Render(const Camera& camera,
              const World& world,
              int recursive_depth) noexcept {
  Canvas canvas(camera.size);

  tbb::parallel_for(tbb::blocked_range<int>(0, canvas.height()),
                    [&](const tbb::blocked_range<int>& br) {
                      for (int y = br.begin(); y < br.end(); ++y) {
                        for (int x = 0; x < canvas.width(); ++x) {
                          const cv::Point p(x, y);
                          const auto ray = camera.RayAt(p);
                          const auto color =
                              world.ColorAt(ray, recursive_depth);
                          canvas.WritePixel(p, color);
                        }
                      }
                    });

  return canvas;
}

}  // namespace rt