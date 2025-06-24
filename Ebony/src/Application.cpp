#include "Application.h"
#include "GLFW/glfw3.h"

#include <glad/glad.h>

#include <cstdlib>
#include <iostream>

namespace Ebony {

Application::Application() {
    // TODO: set GLFW error callback

    if (!glfwInit()) {
        // TODO: Logging
        exit(EXIT_FAILURE);
    }

    appWindow = glfwCreateWindow(1280, 720, "Ebony - Ray Tracing Engine", nullptr, nullptr);
    if (!appWindow) {
        // TOOD: Logging
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(appWindow);

    const int gladStatus = gladLoadGL();
    if (gladStatus == 0) {
        glfwTerminate();
        // TODO: Logging
        exit(EXIT_FAILURE);
    }

    // V-Sync
    glfwSwapInterval(1);

    std::cerr << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

Application::~Application() {
    glfwDestroyWindow(appWindow);
    glfwTerminate();
}

void Application::Run() const {
    while (!glfwWindowShouldClose(appWindow)) {
        glfwSwapBuffers(appWindow);
        glfwPollEvents();
    }
}

} // namespace Ebony
