#pragma once

#include <memory>

namespace Ebony {

class VertexBuffer;
class IndexBuffer;

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) = 0;

    static VertexArray *Create();
};

} // namespace Ebony
