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

void Renderer::UploadSceneToShader(const Scene &scene, const std::shared_ptr<Shader> &shader) {
    const auto &spheres = scene.GetSpheres();
    int sphereCount = static_cast<int>(spheres.size());

    shader->SetUniformInt("u_SphereCount", sphereCount);

    for (int i = 0; i < sphereCount; ++i) {
        const auto &s = spheres[i];

        shader->SetUniformFloat3("u_Spheres[" + std::to_string(i) + "].center", s.center.x, s.center.y, s.center.z);
        shader->SetUniformFloat("u_Spheres[" + std::to_string(i) + "].radius", s.radius);

        shader->SetUniformFloat4("u_Spheres[" + std::to_string(i) + "].material.color", s.material.color.x,
                                 s.material.color.y, s.material.color.z, s.material.color.w);
        shader->SetUniformFloat3("u_Spheres[" + std::to_string(i) + "].material.emission", s.material.emission.x,
                                 s.material.emission.y, s.material.emission.z);
        shader->SetUniformFloat("u_Spheres[" + std::to_string(i) + "].material.emissionStrength",
                                s.material.emissionStrength);
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
