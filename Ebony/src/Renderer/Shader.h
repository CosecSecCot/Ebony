#pragma once

#include <filesystem>
#include <string>

namespace Ebony {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetUniformFloat(const std::string &name, float x) = 0;
    virtual void SetUniformFloat2(const std::string &name, float x, float y) = 0;
    virtual void SetUniformFloat3(const std::string &name, float x, float y, float z) = 0;
    virtual void SetUniformFloat4(const std::string &name, float x, float y, float z, float w) = 0;
    virtual void SetUniformInt(const std::string &name, int x) = 0;
    virtual void SetUniformInt2(const std::string &name, int x, int y) = 0;
    virtual void SetUniformInt3(const std::string &name, int x, int y, int z) = 0;
    virtual void SetUniformInt4(const std::string &name, int x, int y, int z, int w) = 0;
    virtual void SetUniformUInt(const std::string &name, uint32_t x) = 0;
    virtual void SetUniformUInt2(const std::string &name, uint32_t x, uint32_t y) = 0;
    virtual void SetUniformUInt3(const std::string &name, uint32_t x, uint32_t y, uint32_t z) = 0;
    virtual void SetUniformUInt4(const std::string &name, uint32_t x, uint32_t y, uint32_t z, uint32_t w) = 0;

    static Shader *Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    static Shader *CreateFromFiles(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
};

} // namespace Ebony
