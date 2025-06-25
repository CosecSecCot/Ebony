#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ebony {

/**
 * @class Application
 * @brief Responsible for setting up the Rendering context, window creation,
 * running the main loop, and cleaning up resources on exit.
 */
class Application {
public:
    /// Constructs the application and initializes OpenGL/GLFW.
    Application();

    /// Destroys the application and releases all associated resources.
    ~Application();

    /// Runs the main engine loop until the window is closed.
    void Run() const;

private:
    GLFWwindow *appWindow; ///< Handle to the main GLFW window.
};

} // namespace Ebony
