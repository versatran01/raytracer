#pragma once

#include "rt/camera.h"
#include "rt/canvas.h"
#include "rt/world.h"

namespace rt {

Canvas Render(const Camera& camera,
              const World& world,
              int recursize_depth = 1) noexcept;

}