#pragma once

#include "Renderer/Shader.h"

#include <unordered_map>

namespace Ebony {

/**
 * @brief OpenGL implementation of the Shader interface.
 */
class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

    void SetUniformFloat(const std::string &name, float x) override;
    void SetUniformFloat2(const std::string &name, float x, float y) override;
    void SetUniformFloat3(const std::string &name, float x, float y, float z) override;
    void SetUniformFloat4(const std::string &name, float x, float y, float z, float w) override;

private:
    uint32_t rendererID;
    std::unordered_map<std::string, int> uniformLocationCache;

    int GetUniformLocation(const std::string &name);
};

} // namespace Ebony
