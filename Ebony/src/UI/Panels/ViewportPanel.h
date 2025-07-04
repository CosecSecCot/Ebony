#pragma once

#include "Renderer/FrameBuffer.h"
#include "UI/Panel.h"

#include <imgui.h>

#include <memory>

namespace Ebony {

class ViewportPanel : public UIPanel {
public:
    ViewportPanel(const std::shared_ptr<FrameBuffer> &framebuffer, float &aspectRatio, ImVec2 &sceneSize)
        : framebuffer(framebuffer), aspectRatio(aspectRatio), sceneSize(sceneSize) {}

    void Render() override {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");
        sceneSize = ImGui::GetContentRegionAvail();
        if (sceneSize.x > 0 && sceneSize.y > 0 &&
            (framebuffer->GetSpecification().width != (uint32_t)sceneSize.x ||
             framebuffer->GetSpecification().height != (uint32_t)sceneSize.y)) {
            framebuffer->Resize((uint32_t)sceneSize.x, (uint32_t)sceneSize.y);
            aspectRatio = sceneSize.x / sceneSize.y;
        }
        ImGui::Image(framebuffer->GetColorAttachmentRendererID(), sceneSize, ImVec2(0, 1),
                     ImVec2(1, 0) // Flip UVs for OpenGL
        );
        ImGui::End();
        ImGui::PopStyleVar();
    }

private:
    const std::shared_ptr<FrameBuffer> &framebuffer;
    float &aspectRatio;
    ImVec2 &sceneSize;
};

} // namespace Ebony
