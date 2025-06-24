#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ebony {

class Application {
public:
    Application();
    ~Application();

    void Run() const;

private:
    GLFWwindow *appWindow;
};

} // namespace Ebony
