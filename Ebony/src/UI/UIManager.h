#pragma once

#include "Panel.h"

#include <memory>
#include <vector>

struct GLFWwindow;

namespace Ebony {

class UIManager {
public:
    UIManager() = default;
    ~UIManager() = default;

    static void Init(GLFWwindow *window);
    static void SetStyle();
    void Render();
    static void Destroy();

    void RegisterPanel(std::unique_ptr<UIPanel> panel) { panels.emplace_back(std::move(panel)); }

private:
    std::vector<std::unique_ptr<UIPanel>> panels;
};

} // namespace Ebony
