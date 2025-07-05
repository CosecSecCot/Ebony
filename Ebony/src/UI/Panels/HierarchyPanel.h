#pragma once

#include "Renderer/Scene/Scene.h"
#include "UI/Panel.h"

#include <imgui.h>

namespace Ebony {

class HierarchyPanel : public UIPanel {
public:
    HierarchyPanel(Scene &scene, int &selectedIndex) : scene(scene), selectedIndex(selectedIndex) {}

    void Render() override {

        ImGui::Begin(" Hierarchy");

        // Search bar
        char buff[256];
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::InputTextWithHint("##filter", "Filter", buff, sizeof(buff));
        ImGui::Separator();

        if (ImGui::BeginTable("HierarchyTable", 2)) {
            ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Visible", ImGuiTableColumnFlags_WidthFixed, ImGui::GetFrameHeight());

            bool visible = true;
            auto &spheres = scene.GetSpheres();
            for (int i = 0; i < spheres.size(); ++i) {
                std::string label = "󰆧 Sphere " + std::to_string(i);

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::PushID(i);

                // Full-row selectable
                if (ImGui::Selectable("##hierarchy_obj", selectedIndex == i, ImGuiSelectableFlags_SpanAllColumns,
                                      ImVec2(0, ImGui::GetFrameHeight()))) {
                    selectedIndex = i;
                }

                // Draw vertically centered label
                ImVec2 min = ImGui::GetItemRectMin();
                ImVec2 max = ImGui::GetItemRectMax();
                float textY = min.y + (max.y - min.y - ImGui::GetTextLineHeight()) * 0.5f;
                ImGui::SetCursorScreenPos(ImVec2(min.x + ImGui::GetStyle().FramePadding.x, textY));
                ImGui::TextUnformatted(label.c_str());

                // isVisible (Checkbox)
                ImGui::TableSetColumnIndex(1);
                ImGui::Checkbox("##hierarchy_obj_visible", &visible);

                ImGui::PopID();
            }

            ImGui::EndTable();
        }

        ImGui::End();
    }

private:
    Scene &scene;
    int &selectedIndex;
};

} // namespace Ebony
