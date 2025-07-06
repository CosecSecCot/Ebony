#pragma once

#include "Renderer/Scene/Scene.h"
#include "UI/Panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Ebony {

class EnvironmentPanel : public UIPanel {
public:
    EnvironmentPanel(glm::vec3 &skyColorHorizon, glm::vec3 &skyColorZenith, glm::vec3 &groundColor,
                     glm::vec3 &sunLightDirection, float &sunFocus, float &sunIntensity)
        : skyColorHorizon(skyColorHorizon), skyColorZenith(skyColorZenith), groundColor(groundColor),
          sunLightDirection(sunLightDirection), sunFocus(sunFocus), sunIntensity(sunIntensity) {}

    void Render() override {
        ImGui::Begin(" Environment");

        const char *skyType[] = {"Skybox", "Solid Color"};
        static int currentSelection = 0;
        ImGui::Combo("Sky Type", &currentSelection, skyType, IM_ARRAYSIZE(skyType));

        if (strcmp(skyType[currentSelection], "Solid Color") == 0) {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
                               u8" \"Solid Color\" sky has not been implemented yet!");
        }

        if (ImGui::TreeNodeEx("Sky Color", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::BeginDisabled(strcmp(skyType[currentSelection], "Solid Color") == 0);
            ImGui::ColorEdit3("Sky Horizon Color", glm::value_ptr(skyColorHorizon));
            ImGui::ColorEdit3("Sky Zenith Color", glm::value_ptr(skyColorZenith));
            ImGui::ColorEdit3("Ground Color", glm::value_ptr(groundColor));
            ImGui::EndDisabled();
            ImGui::TreePop();
        }

        if (ImGui::TreeNodeEx("Sun Light", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::DragFloat3("Sun Light Direction", glm::value_ptr(sunLightDirection), 0.1f, -1.0f, 1.0f);
            ImGui::DragFloat("Sun Focus", &sunFocus, 0.05f, 0.0f, 100.0f);
            ImGui::DragFloat("Sun Intensity", &sunIntensity, 0.1f, 0.0f, 100.0f);
            ImGui::TreePop();
        }

        ImGui::End();
    }

private:
    glm::vec3 &skyColorHorizon;
    glm::vec3 &skyColorZenith;
    glm::vec3 &groundColor;
    glm::vec3 &sunLightDirection;
    float &sunFocus;
    float &sunIntensity;
};

} // namespace Ebony
