#pragma once

#include "Renderer/Object/Sphere.h"

#include <glm/glm.hpp>

#include <vector>

namespace Ebony {

class Scene {
public:
    void AddSphere(const Sphere &sphere) { m_Spheres.push_back(sphere); }

    std::vector<Sphere> &GetSpheres() { return m_Spheres; }
    [[nodiscard]] const std::vector<Sphere> &GetSpheres() const { return m_Spheres; }

private:
    std::vector<Sphere> m_Spheres;
};

} // namespace Ebony
