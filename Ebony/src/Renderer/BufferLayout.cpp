#include "BufferLayout.h"

namespace Ebony {

uint32_t BufferElement::GetComponentCount() const {
    switch (type) {
    case ShaderDataType::Float:
        return 1;
    case ShaderDataType::Float2:
        return 2;
    case ShaderDataType::Float3:
        return 3;
    case ShaderDataType::Float4:
        return 4;
    case ShaderDataType::Mat3:
        return 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4;
    case ShaderDataType::Int:
        return 1;
    case ShaderDataType::Int2:
        return 2;
    case ShaderDataType::Int3:
        return 3;
    case ShaderDataType::Int4:
        return 4;
    case ShaderDataType::Bool:
        return 1;
    default:
        return 0;
    }
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements) : elements(elements) {
    CalculateOffsetsAndStride();
}

void BufferLayout::CalculateOffsetsAndStride() {
    size_t offset = 0;
    stride = 0;
    for (auto &element : elements) {
        element.offset = offset;
        offset += element.size;
        stride += element.size;
    }
}

} // namespace Ebony
