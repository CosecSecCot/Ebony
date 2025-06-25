#include "Application.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Timer.h"

#include <glad/glad.h>

#include <cstdlib>
#include <iostream>

namespace Ebony {

const char *vertexSrc = R"(
#version 420 core
layout(location = 0) in vec3 a_Position;
void main() {
    gl_Position = vec4(a_Position, 1.0);
}
)";

const char *fragmentSrc = R"(
#version 420 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
)";

static void GLFWErrorCallback(int error, const char *description) {
    std::cerr << "GLFW ERROR: " << description << std::endl;
}

Application::Application() {
    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit()) {
        // TODO: Logging
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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
}

Application::~Application() {
    glfwDestroyWindow(appWindow);
    glfwTerminate();
}

void Application::Run() const {
    std::cerr << "Hello from Ebony Engine!" << std::endl;

    Ebony::Timer timer;

    // === Create triangle data ===
    float vertices[] = {
        0.0f,  0.5f,  0.0f, // top
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f,  -0.5f, 0.0f  // bottom right
    };

    uint32_t indices[] = {0, 1, 2};

    // === Set up buffers ===
    auto vertexArray = std::unique_ptr<Ebony::VertexArray>(Ebony::VertexArray::Create());
    auto vertexBuffer = std::shared_ptr<Ebony::VertexBuffer>(Ebony::VertexBuffer::Create(vertices, sizeof(vertices)));
    vertexBuffer->SetLayout({{Ebony::ShaderDataType::Float3, "a_Position"}});
    vertexArray->AddVertexBuffer(vertexBuffer);

    auto indexBuffer = std::shared_ptr<Ebony::IndexBuffer>(Ebony::IndexBuffer::Create(indices, 3));
    vertexArray->SetIndexBuffer(indexBuffer);

    // === Compile shader manually ===
    auto shader = std::unique_ptr<Ebony::Shader>(Ebony::Shader::Create(vertexSrc, fragmentSrc));

    while (!glfwWindowShouldClose(appWindow)) {
        timer.Tick();

        if (timer.ShouldUpdateFPS()) {
            std::string title = "Ebony - Ray Tracing Engine [" + std::to_string(timer.GetFPS()) + " FPS]";
            glfwSetWindowTitle(appWindow, title.c_str());
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->Bind();
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(appWindow);
        glfwPollEvents();
    }
}

} // namespace Ebony
