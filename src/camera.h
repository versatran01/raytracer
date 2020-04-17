#pragma once

#include <opencv2/core/types.hpp>  // cv::Size

#include "ray.h"        // Ray
#include "transform.h"  // Transform

namespace rt {

struct Camera {
  Camera() = default;
  Camera(cv::Size size, scalar fov, const Transform& t = Transform::Identity())
      : size(size),
        fov(fov),
        half_view(std::tan(fov / 2)),
        pixel_size(half_view * 2 / width()),
        transform(t) {}

  int width() const noexcept { return size.width; }
  int height() const noexcept { return size.height; }
  auto aspect() const noexcept {
    return static_cast<scalar>(width()) / height();
  }

  scalar half_width() const noexcept { return half_view; }
  scalar half_height() const noexcept { return half_view / aspect(); }

  Ray RayAt(cv::Point point) const noexcept;

  cv::Size size;
  scalar fov;  // horizontal fov
  scalar half_view;
  scalar pixel_size;
  Transform transform{Transform::Identity()};
};

}  // namespace rt
