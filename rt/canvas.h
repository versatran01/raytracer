#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "rt/color.h"  // Color

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

  bool IsInside(Index2 index) const noexcept;

  void WritePixel(cv::Point point, const Color& color) noexcept;

  void WritePixel(Index2 index, const Color& color) noexcept;

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

  Color ColorAt(cv::Point point) const noexcept;

  cv::Mat ToBgr() const noexcept;

 private:
  cv::Mat image_;
};

bool SaveCanvas(const Canvas& canvas, const std::string& filename);

}  // namespace rt
