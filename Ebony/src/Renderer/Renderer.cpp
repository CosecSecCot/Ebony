#include "Renderer.h"
#include "Renderer/Buffer.h"

#include <glad/glad.h>

namespace Ebony {

void Renderer::BeginRender() {}

void Renderer::EndRender() {}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray) {
    shader->Bind();
    vertexArray->Bind();
    Renderer::DrawIndexed(vertexArray);
}

void Renderer::Init() {
    // TODO: Handling render commands usage without initializing
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::SetClearColor(const glm::vec4 &color) { glClearColor(color.r, color.g, color.b, color.a); }

void Renderer::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT,
                   nullptr);
}

} // namespace Ebony
