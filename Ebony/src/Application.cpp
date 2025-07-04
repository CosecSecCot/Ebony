#include "Application.h"
#include "Renderer/Buffer.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Timer.h"
#include "UI/Panels/HierarchyPanel.h"
#include "UI/Panels/PropertiesPanel.h"
#include "UI/Panels/ViewportPanel.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

namespace Ebony {
static void GLFWErrorCallback(int error, const char *description) {
    std::cerr << "GLFW ERROR: " << description << std::endl;
}

Application::Application() {
    glfwSetErrorCallback(GLFWErrorCallback);

    if (glfwInit() == GLFW_FALSE) {
        // TODO: Logging
        exit(EXIT_FAILURE);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    appWindow = glfwCreateWindow(1280, 720, "Ebony - OpenGL", nullptr, nullptr);
    if (!appWindow) {
        // TODO: Logging
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(appWindow);

    const int gladStatus = gladLoadGL();
    if (gladStatus == 0) {
        glfwTerminate();
        // TODO: Logging
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(appWindow,
                                   [](GLFWwindow *, int width, int height) { glViewport(0, 0, width, height); });

    // V-Sync
    glfwSwapInterval(1);

    UIManager::Init(appWindow);
}

Application::~Application() {
    glfwDestroyWindow(appWindow);
    glfwTerminate();
}

void Application::Run() {
    Timer timer;

    // clang-format off
    float vertices[] = {
        1.0f,   1.0f,  0.0f,
        1.0f,  -1.0f,  0.0f,
       -1.0f,  -1.0f,  0.0f,
       -1.0f,   1.0f,  0.0f 
    };
    // clang-format on

    uint32_t indices[] = {2, 0, 1, 2, 3, 0};

    auto vertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());
    auto vertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
    vertexBuffer->SetLayout({{ShaderDataType::Float3, "a_Position"}});
    vertexArray->AddVertexBuffer(vertexBuffer);
    auto indexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, 6));
    vertexArray->SetIndexBuffer(indexBuffer);
    auto framebuffer = std::shared_ptr<FrameBuffer>(FrameBuffer::Create(FramebufferSpecification{}));

    auto shader = std::shared_ptr<Shader>(Shader::CreateFromFiles(BASIC_VERT_SHADER_PATH, BASIC_FRAG_SHADER_PATH));

    Scene scene;
    scene.AddSphere({glm::vec3(0.5f, 0.5f, -0.5f), 0.5f, RayTracingMaterial{glm::vec4(1), glm::vec3(1), 0.0f}});
    scene.AddSphere(
        {glm::vec3(0.0f, 0.0f, -2.0f), 0.75f, RayTracingMaterial{glm::vec4(glm::vec3(0.5), 1), glm::vec3(1), 0.0f}});

    Renderer::Init();

    // Uniforms
    float u_AspectRatio = 1280.0f / 720.0f;
    float u_CameraFocalLength = 1.0f;
    float u_ViewPortSize = 2.0f;
    uint32_t u_MaxBounceCount = 3;
    uint32_t u_RaysPerPixel = 2;
    uint32_t u_NumRenderedFrames = 0;

    ImVec2 sceneSize;
    static int selectedSphereIndex = -1;

    ui.RegisterPanel(std::make_unique<ViewportPanel>(framebuffer, u_AspectRatio, sceneSize));
    ui.RegisterPanel(std::make_unique<HierarchyPanel>(scene, selectedSphereIndex));
    ui.RegisterPanel(std::make_unique<PropertiesPanel>(scene, selectedSphereIndex));

    while (!glfwWindowShouldClose(appWindow)) {
        timer.Tick();
        u_NumRenderedFrames++;

        if (timer.ShouldUpdateFPS()) {
            std::stringstream title;
            title << "Ebony - OpenGL " << glGetString(GL_VERSION) << " [" << std::to_string(timer.GetFPS()) << " FPS]";
            glfwSetWindowTitle(appWindow, title.str().c_str());
        }

        Renderer::BeginRender();

        ui.Render();

        framebuffer->Bind();
        Renderer::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Renderer::Clear();
        shader->Bind();
        shader->SetUniformUInt2("u_ImageDimensions", static_cast<uint32_t>(sceneSize.x),
                                static_cast<uint32_t>(sceneSize.y));
        shader->SetUniformFloat("u_AspectRatio", u_AspectRatio);
        shader->SetUniformFloat("u_CameraFocalLength", u_CameraFocalLength);
        shader->SetUniformFloat("u_ViewPortSize", u_ViewPortSize);
        shader->SetUniformUInt("u_MaxBounceCount", u_MaxBounceCount);
        shader->SetUniformUInt("u_RaysPerPixel", u_RaysPerPixel);
        shader->SetUniformUInt("u_NumRenderedFrames", u_NumRenderedFrames);
        // shader.SetUniform3f("u_SkyColorHorizon", u_SkyColorHorizon.x, u_SkyColorHorizon.y, u_SkyColorHorizon.z);
        // shader.SetUniform3f("u_SkyColorZenith", u_SkyColorZenith.x, u_SkyColorZenith.y, u_SkyColorZenith.z);
        // shader.SetUniform3f("u_GroundColor", u_GroundColor.x, u_GroundColor.y, u_GroundColor.z);
        // shader.SetUniform3f("u_SunLightDirection", u_SunLightDirection.x, u_SunLightDirection.y,
        // u_SunLightDirection.z);
        // shader.SetUniform1f("u_SunFocus", u_SunFocus);
        // shader.SetUniform1f("u_SunIntensity", u_SunIntensity);
        Renderer::UploadSceneToShader(scene, shader);
        Renderer::Submit(shader, vertexArray);
        framebuffer->Unbind();

        Renderer::EndRender();

        glfwSwapBuffers(appWindow);
        glfwPollEvents();
    }
}

} // namespace Ebony
