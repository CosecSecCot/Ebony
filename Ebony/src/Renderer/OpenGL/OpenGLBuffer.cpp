#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Ebony {

// ----------- OpenGLVertexBuffer -----------

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) : rendererID(0) {
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) : rendererID(0) {
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &rendererID); }

void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, rendererID); }

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// TODO: Check if correct
void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

// ----------- OpenGLIndexBuffer -----------

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : rendererID(0), count(count) {
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);

    // Since `count` is not going to be very large to cause overflow, we can just ignore the compile warning here.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &rendererID); }

void OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID); }

void OpenGLIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

uint32_t OpenGLIndexBuffer::GetCount() const { return count; }

} // namespace Ebony
