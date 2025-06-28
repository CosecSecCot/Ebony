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

    static Shader *Create(const std::string &vertexSrc, const std::string &fragmentSrc);
    static Shader *CreateFromFiles(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
};

} // namespace Ebony
