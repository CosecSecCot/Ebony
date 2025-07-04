#include "OpenGLShader.h"

#include <glad/glad.h>

#include <iostream>

namespace Ebony {

static GLuint CompileShader(GLenum type, const std::string &src) {
    GLuint shader = glCreateShader(type);
    const char *cSrc = src.c_str();
    glShaderSource(shader, 1, &cSrc, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "Shader Compilation Error: " << log << std::endl;
    }

    return shader;
}

OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc) {
    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    rendererID = glCreateProgram();
    glAttachShader(rendererID, vertex);
    glAttachShader(rendererID, fragment);
    glLinkProgram(rendererID);

    int success;
    glGetProgramiv(rendererID, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(rendererID, 1024, nullptr, log);
        std::cerr << "Shader Linking Error: " << log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(rendererID); }

void OpenGLShader::Bind() const { glUseProgram(rendererID); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

int OpenGLShader::GetUniformLocation(const std::string &name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }

    int location = glGetUniformLocation(rendererID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' not found!" << std::endl;
    }

    uniformLocationCache[name] = location;
    return location;
}

void OpenGLShader::SetUniformFloat(const std::string &name, float x) { glUniform1f(GetUniformLocation(name), x); }

void OpenGLShader::SetUniformFloat2(const std::string &name, float x, float y) {
    glUniform2f(GetUniformLocation(name), x, y);
}

void OpenGLShader::SetUniformFloat3(const std::string &name, float x, float y, float z) {
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void OpenGLShader::SetUniformFloat4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void OpenGLShader::SetUniformInt(const std::string &name, int x) { glUniform1i(GetUniformLocation(name), x); }

void OpenGLShader::SetUniformInt2(const std::string &name, int x, int y) {
    glUniform2i(GetUniformLocation(name), x, y);
}

void OpenGLShader::SetUniformInt3(const std::string &name, int x, int y, int z) {
    glUniform3i(GetUniformLocation(name), x, y, z);
}

void OpenGLShader::SetUniformInt4(const std::string &name, int x, int y, int z, int w) {
    glUniform4i(GetUniformLocation(name), x, y, z, w);
}

void OpenGLShader::SetUniformUInt(const std::string &name, uint32_t x) { glUniform1ui(GetUniformLocation(name), x); }

void OpenGLShader::SetUniformUInt2(const std::string &name, uint32_t x, uint32_t y) {
    glUniform2ui(GetUniformLocation(name), x, y);
}

void OpenGLShader::SetUniformUInt3(const std::string &name, uint32_t x, uint32_t y, uint32_t z) {
    glUniform3ui(GetUniformLocation(name), x, y, z);
}

void OpenGLShader::SetUniformUInt4(const std::string &name, uint32_t x, uint32_t y, uint32_t z, uint32_t w) {
    glUniform4ui(GetUniformLocation(name), x, y, z, w);
}

} // namespace Ebony
