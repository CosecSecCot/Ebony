#pragma once

#include "Renderer/Scene/Scene.h"
#include "UI/Panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Ebony {

class SettingsPanel : public UIPanel {
public:
    SettingsPanel(const float &cameraFocalLength, float &viewPortSize, int &maxBounceCount, int &raysPerPixel)
        : cameraFocalLength(cameraFocalLength), viewPortSize(viewPortSize), maxBounceCount(maxBounceCount),
          raysPerPixel(raysPerPixel) {}

    void Render() override {
        ImGui::Begin(" Settings");

        ImGui::DragFloat("Viewport Size", &viewPortSize, 0.01f, cameraFocalLength, FLT_MAX);
        ImGui::SliderInt("Ray Bounce Count", &maxBounceCount, 1, 10);
        ImGui::SliderInt("Rays Per Pixel", &raysPerPixel, 1, 100);

        ImGui::End();
    }

private:
    const float &cameraFocalLength;
    float &viewPortSize;
    int &maxBounceCount;
    int &raysPerPixel;
};

} // namespace Ebony