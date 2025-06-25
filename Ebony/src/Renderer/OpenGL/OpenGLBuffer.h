#pragma once

#include "Renderer/Buffer.h"

namespace Ebony {

/**
 * @class OpenGLVertexBuffer
 * @brief OpenGL implementation of the VertexBuffer interface.
 */
class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(uint32_t size);
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    ~OpenGLVertexBuffer() override;

    void SetLayout(const BufferLayout &l) override { layout = l; }
    [[nodiscard]] const BufferLayout &GetLayout() const override { return layout; }

    void Bind() const override;
    void Unbind() const override;
    void SetData(const void *data, uint32_t size) override;

private:
    uint32_t rendererID;
    BufferLayout layout;
};

/**
 * @class OpenGLIndexBuffer
 * @brief OpenGL implementation of the IndexBuffer interface.
 */
class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    [[nodiscard]] uint32_t GetCount() const override;

private:
    uint32_t rendererID;
    uint32_t count;
};

} // namespace Ebony
