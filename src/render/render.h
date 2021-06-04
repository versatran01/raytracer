#pragma once

#include "render/camera.h"
#include "render/canvas.h"
#include "render/world.h"

namespace rt {

Canvas Render(const Camera& camera,
              const World& world,
              int recursize_depth = 1) noexcept;

}