#include "logging.h"
#include "tuple.h"

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
  Projectile p{Point3(0, 1, 0), Normalized(Vector3(1, 1, 0))};
  const Environment e{Vector3(0, -0.1, 0), Vector3(-0.01, 0, 0)};

  while (p.position.y() > 0) {
    p = Tick(e, p);
    LOG(INFO) << "position: " << p.position.transpose();
  }
}