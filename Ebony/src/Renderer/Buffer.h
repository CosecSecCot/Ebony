#pragma once

#include "Renderer/BufferLayout.h"

#include <cstdint>

namespace Ebony {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void SetData(const void *data, uint32_t size) = 0;

    virtual void SetLayout(const BufferLayout &layout) = 0;
    [[nodiscard]] virtual const BufferLayout &GetLayout() const = 0;

    static VertexBuffer *Create(uint32_t size); // Factory
    static VertexBuffer *Create(float *vertices, uint32_t size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual uint32_t GetCount() const = 0;

    static IndexBuffer *Create(uint32_t *indices, uint32_t count);
};

} // namespace Ebony
