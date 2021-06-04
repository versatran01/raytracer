#include <glog/logging.h>

#include <opencv2/highgui.hpp>

#include "canvas.h"
#include "core/tuple.h"

using namespace rt;

struct Projectile {
  Point3 position;
  Vector3 velocity;
};

struct Environment {
  Vector3 gravity;
  Vector3 wind;
};

Projectile Tick(const Environment& env, const Projectile& proj) {
  return {proj.position + proj.velocity,
          proj.velocity + env.gravity + env.wind};
}

int main(int argc, char** argv) {
  const Point3 start(0, 1, 0);
  const auto velocity = Normalized(Vector3(1, 1.8, 0)) * 11.25;
  Projectile p{start, velocity};

  const Vector3 gravity(0, -0.1, 0);
  const Vector3 wind(-0.01, 0, 0);
  const Environment e{gravity, wind};

  Canvas c({900, 550});

  const Color red(1, 0, 0);

  while (p.position.y() > 0) {
    p = Tick(e, p);
    LOG(INFO) << "y: " << p.position.y();

    c.WritePixel(cv::Point2i{static_cast<int>(std::round(p.position.x())),
                             static_cast<int>(std::round(p.position.y()))},
                 red);

    cv::imshow("canvas", c.ToBgr());
    cv::waitKey(1);
  }
}
