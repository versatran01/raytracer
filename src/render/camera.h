#pragma once

#include <opencv2/core/types.hpp>  // cv::Size

#include "core/ray.h"        // Ray
#include "core/transform.h"  // Transform

namespace rt {

struct Camera {
  Camera() = default;
  Camera(cv::Size size, scalar fov, const Transform& t = Transform::Identity());

  int width() const noexcept { return size.width; }
  int height() const noexcept { return size.height; }
  scalar aspect() const noexcept {
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
