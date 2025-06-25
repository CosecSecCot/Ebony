#include "Renderer/Buffer.h"
#include "Renderer/OpenGL/OpenGLBuffer.h"

namespace Ebony {

VertexBuffer *VertexBuffer::Create(uint32_t size) { return new OpenGLVertexBuffer(size); }

VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) { return new OpenGLVertexBuffer(vertices, size); }

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t count) { return new OpenGLIndexBuffer(indices, count); }

} // namespace Ebony
