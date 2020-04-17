#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "color.h"  // Color

namespace rt {

using Pixel = cv::Vec3d;
using Vector2i = Eigen::Vector2i;

struct Index2 {
  Index2() = default;
  Index2(int r, int c) : rc{r, c} {}

  int row() const noexcept { return rc[0]; }
  int col() const noexcept { return rc[1]; }

  int rc[2] = {0, 0};
};

class Canvas {
 public:
  Canvas() = default;

  // size(width, height)
  explicit Canvas(cv::Size size)
      : image_(size, CV_64FC3, cv::Scalar(0, 0, 0)) {}

  int width() const noexcept { return image_.cols; }
  int height() const noexcept { return image_.rows; }
  const cv::Mat& image() const noexcept { return image_; }

  bool IsInside(Index2 index) const noexcept {
    return 0 <= index.row() && index.row() < height() && 0 <= index.col() &&
           index.col() < width();
  }

  void WritePixel(cv::Point point, const Color& color) noexcept {
    return WritePixel(Index2{point.y, point.x}, color);
  }

  void WritePixel(Index2 index, const Color& color) noexcept {
    if (!IsInside(index)) return;
    auto& pixel = at(index);
    pixel[0] = color.r();
    pixel[1] = color.g();
    pixel[2] = color.b();
  }

  const Pixel& at(cv::Point point) const noexcept {
    return image_.at<Pixel>(point);
  }

  Pixel& at(cv::Point point) noexcept { return image_.at<Pixel>(point); }

  const Pixel& at(Index2 index) const noexcept {
    return image_.at<Pixel>(index.row(), index.col());
  }

  Pixel& at(Index2 index) noexcept {
    return image_.at<Pixel>(index.row(), index.col());
  }

  Color color_at(cv::Point point) const noexcept {
    const auto pixel = at(point);
    return {pixel[0], pixel[1], pixel[2]};
  }

  cv::Mat ToBgr() const noexcept {
    // first convert to 255
    cv::Mat bgr;
    image_.convertTo(bgr, CV_8UC3, 255);
    cv::cvtColor(bgr, bgr, cv::COLOR_RGB2BGR);
    return bgr;
  }

 private:
  cv::Mat image_;
};

inline bool SaveCanvas(const Canvas& canvas, const std::string& filename) {
  return cv::imwrite(filename, canvas.ToBgr());
}

}  // namespace rt
