#pragma once

#include "camera.h"
#include "canvas.h"
#include "world.h"

namespace rt {

Canvas Render(const Camera& camera,
              const World& world,
              int recursize_depth = 1) noexcept;

}