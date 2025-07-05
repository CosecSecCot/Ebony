#pragma once

#include "Renderer/Scene/Scene.h"
#include "UI/Panel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace Ebony {

class PropertiesPanel : public UIPanel {
public:
    PropertiesPanel(Scene &scene, int &selectedIndex) : scene(scene), selectedIndex(selectedIndex) {}

    void Render() override {
        auto &spheres = scene.GetSpheres();
        ImGui::Begin("󰖷 Properties");
        if (selectedIndex >= 0 && selectedIndex < spheres.size()) {
            Sphere &s = spheres[selectedIndex];

            if (ImGui::TreeNodeEx("󰵉 Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::DragFloat3("Position", glm::value_ptr(s.center), 0.01f);
                ImGui::DragFloat("Radius", &s.radius, 0.01f);
                ImGui::TreePop();
            }
            if (ImGui::TreeNodeEx("󰆦 Material", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::ColorEdit4("Color", glm::value_ptr(s.material.color));
                ImGui::ColorEdit3("Emission", glm::value_ptr(s.material.emission));
                ImGui::DragFloat("Emission Strength", &s.material.emissionStrength, 0.01f);
                ImGui::TreePop();
            }
        }
        ImGui::End();
    }

private:
    Scene &scene;
    int &selectedIndex;
};

} // namespace Ebony
