#include "Renderer/Framebuffer.h"
#include "Renderer/OpenGL/OpenGLFramebuffer.h"

namespace Ebony {

FrameBuffer *FrameBuffer::Create(const FramebufferSpecification &spec) { return new OpenGLFrameBuffer(spec); }

} // namespace Ebony
