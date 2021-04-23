#include "camera.h"

namespace rt {

Camera::Camera(cv::Size size, scalar fov, const Transform& t)
    : size(size),
      fov(fov),
      half_view(std::tan(fov / 2)),
      pixel_size(half_view * 2 / width()),
      transform(t) {}

Ray Camera::RayAt(cv::Point point) const noexcept {
  const auto world_x = half_width() - point.x * pixel_size;
  const auto world_y = half_height() - point.y * pixel_size;

  const Transform inv = transform.inverse();
  const Point3 pixel = inv * Point3(world_x, world_y, -1);
  const Point3 origin = inv * Point3::Zero();
  const Vector3 direction = Normalized(pixel - origin);
  return {origin, direction};
}

}  // namespace rt
