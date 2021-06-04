#include "rt/canvas.h"

namespace rt {

bool Canvas::IsInside(Index2 index) const noexcept {
  return 0 <= index.row() && index.row() < height() && 0 <= index.col() &&
         index.col() < width();
}

void Canvas::WritePixel(cv::Point point, const Color& color) noexcept {
  return WritePixel(Index2{point.y, point.x}, color);
}

void Canvas::WritePixel(Index2 index, const Color& color) noexcept {
  if (!IsInside(index)) return;
  auto& pixel = at(index);
  pixel[0] = color.r();
  pixel[1] = color.g();
  pixel[2] = color.b();
}

Color Canvas::ColorAt(cv::Point point) const noexcept {
  const auto pixel = at(point);
  return {pixel[0], pixel[1], pixel[2]};
}

cv::Mat Canvas::ToBgr() const noexcept {
  // first convert to 255
  cv::Mat bgr;
  image_.convertTo(bgr, CV_8UC3, 255);
  cv::cvtColor(bgr, bgr, cv::COLOR_RGB2BGR);
  return bgr;
}

bool SaveCanvas(const Canvas& canvas, const std::string& filename) {
  return cv::imwrite(filename, canvas.ToBgr());
}

}  // namespace rt
