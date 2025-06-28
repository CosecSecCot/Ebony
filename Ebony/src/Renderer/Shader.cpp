#include "Renderer/Shader.h"
#include "Renderer/OpenGL/OpenGLShader.h"
#include "Utils/FileUtils.h"

namespace Ebony {

Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
    return new OpenGLShader(vertexSrc, fragmentSrc);
}

Shader *Shader::CreateFromFiles(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath) {
    using namespace Ebony::FileUtils;
    std::string vertexSrc = ReadFileAsString(vertexPath);
    std::string fragmentSrc = ReadFileAsString(fragmentPath);
    return new OpenGLShader(vertexSrc, fragmentSrc);
}

} // namespace Ebony
