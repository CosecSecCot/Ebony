#pragma once

#include <cstdint>

namespace Ebony {

/**
 * @brief Specification struct for creating a framebuffer.
 */
struct FramebufferSpecification {
    uint32_t width = 1280;
    uint32_t height = 720;
};

/**
 * @brief Abstract API-agnostic Framebuffer interface.
 */
class FrameBuffer {
public:
    virtual ~FrameBuffer() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void Resize(uint32_t width, uint32_t height) = 0;

    [[nodiscard]] virtual uint32_t GetColorAttachmentRendererID() const = 0;
    [[nodiscard]] virtual const FramebufferSpecification &GetSpecification() const = 0;

    static FrameBuffer *Create(const FramebufferSpecification &spec);
};

} // namespace Ebony
