#include "Renderer.h"
#include "Renderer/Buffer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ebony {

void Renderer::BeginRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::EndRender() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}

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
