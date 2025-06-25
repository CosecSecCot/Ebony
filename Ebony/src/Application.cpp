#include "Application.h"
#include "GLFW/glfw3.h"
#include "Timer.h"

#include <glad/glad.h>

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

    while (!glfwWindowShouldClose(appWindow)) {
        timer.Tick();

        if (timer.ShouldUpdateFPS()) {
            std::string title = "Ebony - Ray Tracing Engine [" + std::to_string(timer.GetFPS()) + " FPS]";
            glfwSetWindowTitle(appWindow, title.c_str());
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(appWindow);
        glfwPollEvents();
    }
}

} // namespace Ebony
