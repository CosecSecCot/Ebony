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
    void SetUniformInt(const std::string &name, int x) override;
    void SetUniformInt2(const std::string &name, int x, int y) override;
    void SetUniformInt3(const std::string &name, int x, int y, int z) override;
    void SetUniformInt4(const std::string &name, int x, int y, int z, int w) override;
    void SetUniformUInt(const std::string &name, uint32_t x) override;
    void SetUniformUInt2(const std::string &name, uint32_t x, uint32_t y) override;
    void SetUniformUInt3(const std::string &name, uint32_t x, uint32_t y, uint32_t z) override;
    void SetUniformUInt4(const std::string &name, uint32_t x, uint32_t y, uint32_t z, uint32_t w) override;

private:
    uint32_t rendererID;
    std::unordered_map<std::string, int> uniformLocationCache;

    int GetUniformLocation(const std::string &name);
};

} // namespace Ebony
