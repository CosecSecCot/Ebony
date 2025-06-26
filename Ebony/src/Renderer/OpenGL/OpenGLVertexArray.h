#pragma once

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include <vector>

namespace Ebony {

/**
 * @class OpenGLVertexArray
 * @brief OpenGL implementation of the VertexArray abstraction.
 * 
 * Manages VAO creation, binding, and attribute layout setup.
 */
class OpenGLVertexArray : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
    void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override;

    [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override {
        return vertexBuffers;
    }
    [[nodiscard]] const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override { return indexBuffer; }

private:
    uint32_t rendererID;
    uint32_t attributeIndex = 0;

    std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
    std::shared_ptr<IndexBuffer> indexBuffer;
};

} // namespace Ebony
