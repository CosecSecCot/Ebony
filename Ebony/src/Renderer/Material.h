#pragma once

#include <glm/glm.hpp>

namespace Ebony {

struct RayTracingMaterial {
    glm::vec4 color;        // 16 bytes
    glm::vec3 emission;     // 12 bytes
    float emissionStrength; // 4 bytes
};

} // namespace Ebony
