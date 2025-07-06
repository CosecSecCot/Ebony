#pragma once

#include "Renderer/Scene/Scene.h"
#include "UI/Panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Ebony {

class CameraPanel : public UIPanel {
public:
    CameraPanel(float &cameraFocalLength) : focalLength(cameraFocalLength) {}

    void Render() override {
        ImGui::Begin(" Camera");

        ImGui::DragFloat("Focal Length", &focalLength, 0.1f, 0.0f, FLT_MAX);

        ImGui::End();
    }

private:
    float &focalLength;
};

} // namespace Ebony
