#pragma once

#include <memory>
#include <vector>

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

    [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
    [[nodiscard]] virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;

    static VertexArray *Create();
};

} // namespace Ebony
