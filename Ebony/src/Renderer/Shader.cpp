#include "Renderer/Shader.h"
#include "Renderer/OpenGL/OpenGLShader.h"

namespace Ebony {

Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
    return new OpenGLShader(vertexSrc, fragmentSrc);
}

} // namespace Ebony
