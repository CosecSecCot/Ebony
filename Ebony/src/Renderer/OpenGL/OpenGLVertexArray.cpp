#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include <cassert>

namespace Ebony {

OpenGLVertexArray::OpenGLVertexArray() : rendererID(0) { glGenVertexArrays(1, &rendererID); }

OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &rendererID); }

void OpenGLVertexArray::Bind() const { glBindVertexArray(rendererID); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
    assert(vertexBuffer && "VertexBuffer is null!");
    vertexBuffers.push_back(vertexBuffer);

    Bind();
    vertexBuffer->Bind();

    // // Layout hardcoded for now: 3 floats (position)
    // glEnableVertexAttribArray(attributeIndex);
    // glVertexAttribPointer(attributeIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<const void *>(0));
    // attributeIndex++;

    const auto &layout = vertexBuffer->GetLayout();
    assert(layout.GetElements().size() && "VertexBuffer has no layout!");

    for (const auto &element : layout.GetElements()) {
        glEnableVertexAttribArray(attributeIndex);
        glVertexAttribPointer(attributeIndex, static_cast<GLint>(element.GetComponentCount()),
                              ShaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE,
                              static_cast<GLint>(layout.GetStride()), reinterpret_cast<const void *>(element.offset));
        attributeIndex++;
    }
}

void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) {
    assert(indexBuffer && "IndexBuffer is null!");
    this->indexBuffer = indexBuffer;

    Bind();
    indexBuffer->Bind();
}

} // namespace Ebony
