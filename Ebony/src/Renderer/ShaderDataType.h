#pragma once

#include <glad/glad.h>

#include <cassert>
#include <cstdint>

namespace Ebony {

/**
 * @brief Represents a data type used in vertex attributes.
 */
enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

/**
 * @brief Returns the size in bytes of a given ShaderDataType.
 */
static uint32_t ShaderDataTypeSize(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    default:
        return 0;
    }
}

/**
 * @brief Returns the corresponding OpenGL base type for a given ShaderDataType.
 */
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
        return GL_FLOAT;

    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
        return GL_INT;

    case ShaderDataType::Bool:
        return GL_BOOL;

    default:
        assert(false && "Invalid DataType");
        return 0; // Invalid type
    }
}

} // namespace Ebony
