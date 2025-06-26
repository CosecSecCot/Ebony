#pragma once

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Ebony {

/**
 * @brief High-level renderer API. Hides backend-specific calls.
 */
class Renderer {
public:
    static void BeginRender(); // Later: pass camera, viewProj
    static void EndRender();

    static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray);

    static void Init();
    static void Clear();
    static void SetClearColor(const glm::vec4 &color);

private:
    static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray);
};

} // namespace Ebony
