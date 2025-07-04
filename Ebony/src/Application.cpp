#include "Application.h"
#include "Renderer/Buffer.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Timer.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cstdlib>
#include <iostream>

namespace Ebony {
static void GLFWErrorCallback(int error, const char *description) {
    std::cerr << "GLFW ERROR: " << description << std::endl;
}

Application::Application() {
    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit()) {
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

    appWindow = glfwCreateWindow(1280, 720, "Ebony - Ray Tracing Engine", nullptr, nullptr);
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

    std::cerr << "Ebony Engine Initialized!" << std::endl;
    std::cerr << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Credits: https://github.com/ocornut/imgui/issues/707#issuecomment-2605839926
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // Base Colors
    ImVec4 bgColor = ImVec4(0.10f, 0.105f, 0.11f, 1.00f);
    ImVec4 lightBgColor = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
    ImVec4 panelColor = ImVec4(0.17f, 0.18f, 0.19f, 1.00f);
    ImVec4 panelHoverColor = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    ImVec4 panelActiveColor = ImVec4(0.23f, 0.26f, 0.29f, 1.00f);
    ImVec4 textColor = ImVec4(0.86f, 0.87f, 0.88f, 1.00f);
    ImVec4 textDisabledColor = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    ImVec4 borderColor = ImVec4(0.14f, 0.16f, 0.18f, 1.00f);

    // Text
    colors[ImGuiCol_Text] = textColor;
    colors[ImGuiCol_TextDisabled] = textDisabledColor;

    // Windows
    colors[ImGuiCol_WindowBg] = bgColor;
    colors[ImGuiCol_ChildBg] = bgColor;
    colors[ImGuiCol_PopupBg] = bgColor;
    colors[ImGuiCol_Border] = borderColor;
    colors[ImGuiCol_BorderShadow] = borderColor;

    // Headers
    colors[ImGuiCol_Header] = panelColor;
    colors[ImGuiCol_HeaderHovered] = panelHoverColor;
    colors[ImGuiCol_HeaderActive] = panelActiveColor;

    // Buttons
    colors[ImGuiCol_Button] = panelColor;
    colors[ImGuiCol_ButtonHovered] = panelHoverColor;
    colors[ImGuiCol_ButtonActive] = panelActiveColor;

    // Frame BG
    colors[ImGuiCol_FrameBg] = lightBgColor;
    colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
    colors[ImGuiCol_FrameBgActive] = panelActiveColor;

    // Tabs
    colors[ImGuiCol_Tab] = panelColor;
    colors[ImGuiCol_TabHovered] = panelHoverColor;
    colors[ImGuiCol_TabActive] = panelActiveColor;
    colors[ImGuiCol_TabUnfocused] = panelColor;
    colors[ImGuiCol_TabUnfocusedActive] = panelHoverColor;

    // Title
    colors[ImGuiCol_TitleBg] = bgColor;
    colors[ImGuiCol_TitleBgActive] = bgColor;
    colors[ImGuiCol_TitleBgCollapsed] = bgColor;

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = bgColor;
    colors[ImGuiCol_ScrollbarGrab] = panelColor;
    colors[ImGuiCol_ScrollbarGrabHovered] = panelHoverColor;
    colors[ImGuiCol_ScrollbarGrabActive] = panelActiveColor;

    // Checkmark
    colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

    // Slider
    colors[ImGuiCol_SliderGrab] = panelHoverColor;
    colors[ImGuiCol_SliderGrabActive] = panelActiveColor;

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = panelColor;
    colors[ImGuiCol_ResizeGripHovered] = panelHoverColor;
    colors[ImGuiCol_ResizeGripActive] = panelActiveColor;

    // Separator
    colors[ImGuiCol_Separator] = borderColor;
    colors[ImGuiCol_SeparatorHovered] = panelHoverColor;
    colors[ImGuiCol_SeparatorActive] = panelActiveColor;

    // Plot
    colors[ImGuiCol_PlotLines] = textColor;
    colors[ImGuiCol_PlotLinesHovered] = panelActiveColor;
    colors[ImGuiCol_PlotHistogram] = textColor;
    colors[ImGuiCol_PlotHistogramHovered] = panelActiveColor;

    // Text Selected BG
    colors[ImGuiCol_TextSelectedBg] = panelActiveColor;

    // Modal Window Dim Bg
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.105f, 0.11f, 0.5f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = panelColor;
    colors[ImGuiCol_TableBorderStrong] = borderColor;
    colors[ImGuiCol_TableBorderLight] = borderColor;
    colors[ImGuiCol_TableRowBg] = bgColor;
    colors[ImGuiCol_TableRowBgAlt] = lightBgColor;

    // Styles
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 2.0f;
    style.WindowBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 2.0f;
    style.GrabMinSize = 7.0f;
    style.GrabRounding = 2.0f;
    style.TabBorderSize = 1.0f;
    style.TabRounding = 2.0f;

    // Reduced Padding and Spacing
    style.WindowPadding = ImVec2(5.0f, 5.0f);
    style.WindowBorderSize = 0;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.ItemSpacing = ImVec2(6.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);

    // Font Scaling
    io.FontGlobalScale = 1.0f;
    float baseFontSize = 14.0f;
    float iconFontSize = baseFontSize * 2.0f / 3.0f;
    // io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF(INTER_FONT_PATH, baseFontSize);

    ImGui_ImplGlfw_InitForOpenGL(appWindow, true);
#ifdef __APPLE__
    ImGui_ImplOpenGL3_Init("#version 410");
#else
    ImGui_ImplOpenGL3_Init("#version 420");
#endif
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(appWindow);
    glfwTerminate();
}

void Application::Run() const {
    std::cerr << "Hello from Ebony Engine!" << std::endl;

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

    while (!glfwWindowShouldClose(appWindow)) {
        timer.Tick();
        u_NumRenderedFrames++;

        if (timer.ShouldUpdateFPS()) {
            std::string title = "Ebony - Ray Tracing Engine [" + std::to_string(timer.GetFPS()) + " FPS]";
            glfwSetWindowTitle(appWindow, title.c_str());
        }

        Renderer::BeginRender();

        // GUI
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGui::DockSpaceOverViewport(-1, ImGui::GetMainViewport());
        }

        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit")) {
                break;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");
        ImVec2 sceneSize = ImGui::GetContentRegionAvail();
        if (sceneSize.x > 0 && sceneSize.y > 0 &&
            (framebuffer->GetSpecification().width != (uint32_t)sceneSize.x ||
             framebuffer->GetSpecification().height != (uint32_t)sceneSize.y)) {
            framebuffer->Resize((uint32_t)sceneSize.x, (uint32_t)sceneSize.y);
            u_AspectRatio = sceneSize.x / sceneSize.y;
        }
        ImGui::Image(framebuffer->GetColorAttachmentRendererID(), sceneSize, ImVec2(0, 1),
                     ImVec2(1, 0) // Flip UVs for OpenGL
        );
        ImGui::End();
        ImGui::PopStyleVar();

        static int selectedSphereIndex = -1;
        auto &spheres = scene.GetSpheres();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Hierarchy");
        if (ImGui::TreeNodeEx("Scene", ImGuiTreeNodeFlags_DefaultOpen)) {
            for (int i = 0; i < spheres.size(); i++) {
                std::string name = "Sphere " + std::to_string(i);
                if (ImGui::Selectable(name.c_str(), selectedSphereIndex == i)) {
                    selectedSphereIndex = i;
                }
            }
            ImGui::TreePop();
        }
        ImGui::Indent(6.0f);
        if (ImGui::Selectable("Environmental Lighting", false)) {
        }
        if (ImGui::Selectable("Main Camera", false)) {
        }
        ImGui::Unindent(6.0f);
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Properties");
        if (selectedSphereIndex >= 0 && selectedSphereIndex < spheres.size()) {
            Sphere &s = spheres[selectedSphereIndex];

            if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::DragFloat3("Position", glm::value_ptr(s.center), 0.01f);
                ImGui::DragFloat("Radius", &s.radius, 0.01f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNodeEx("Material", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::ColorEdit4("Color", glm::value_ptr(s.material.color));
                ImGui::ColorEdit3("Emission", glm::value_ptr(s.material.emission));
                ImGui::DragFloat("Emission Strength", &s.material.emissionStrength, 0.01f);
                ImGui::TreePop();
            }
        }
        ImGui::End();

        // Rendering
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
