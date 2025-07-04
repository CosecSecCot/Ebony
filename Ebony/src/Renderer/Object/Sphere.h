#pragma once

#include "Renderer/Material.h"
#include <glm/glm.hpp>

namespace Ebony {

struct Sphere {
    glm::vec3 center;                   // 12 bytes
    float radius;                       // 4 bytes
    Ebony::RayTracingMaterial material; // 32 bytes
};

} // namespace Ebony
