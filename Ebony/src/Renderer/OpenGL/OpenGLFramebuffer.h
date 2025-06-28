#pragma once

#include "Renderer/Framebuffer.h"

namespace Ebony {

/**
 * @brief OpenGL implementation of the Framebuffer interface.
 */
class OpenGLFrameBuffer : public FrameBuffer {
public:
    OpenGLFrameBuffer(const FramebufferSpecification &spec);
    ~OpenGLFrameBuffer() override;

    void Bind() override;
    void Unbind() override;

    void Resize(uint32_t width, uint32_t height) override;

    [[nodiscard]] uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }
    [[nodiscard]] const FramebufferSpecification &GetSpecification() const override { return specification; }

private:
    void Invalidate();

private:
    uint32_t rendererID = 0;
    uint32_t colorAttachment = 0;
    uint32_t depthAttachment = 0;

    FramebufferSpecification specification;
};

} // namespace Ebony
