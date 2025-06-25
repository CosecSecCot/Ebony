#include "Renderer/VertexArray.h"
#include "Renderer/OpenGL/OpenGLVertexArray.h"

namespace Ebony {

VertexArray *VertexArray::Create() { return new OpenGLVertexArray(); }

} // namespace Ebony
