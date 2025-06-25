#pragma once

#include "ShaderDataType.h"

#include <string>
#include <vector>

namespace Ebony {

/**
 * @struct BufferElement
 * @brief Represents a single attribute in a vertex buffer.
 * 
 * Each BufferElement corresponds to one input in a shader (e.g., vec3 position, vec2 texCoord).
 * It contains metadata like type, name, size in bytes, offset from the start of the vertex, and normalization.
 */
struct BufferElement {
    std::string name;                           ///< Name of the attribute (e.g., "a_Position")
    ShaderDataType type = ShaderDataType::None; ///< Type of the data (e.g., Float3)
    uint32_t size{};                            ///< Size of the element in bytes
    size_t offset{};                            ///< Offset from the start of the vertex
    bool normalized{};                          ///< Whether the attribute should be normalized (for fixed-point data)

    /**
     * @brief Constructs a BufferElement with the given type and name.
     * 
     * @param type The ShaderDataType of the attribute (e.g., Float3).
     * @param name The name of the attribute as it appears in the shader.
     * @param normalized Whether the attribute should be normalized.
     */
    BufferElement(ShaderDataType type, std::string name, bool normalized = false)
        : name(std::move(name)), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

    /// Default constructor
    BufferElement() = default;

    /**
     * @brief Returns the number of components in this element.
     * 
     * For example, a Float3 returns 3, and Mat4 returns 16.
     * @return Number of components.
     */
    [[nodiscard]] uint32_t GetComponentCount() const;
};

/**
 * @class BufferLayout
 * @brief Describes the structure of a vertex — how multiple BufferElements are laid out.
 * 
 * The layout defines attribute order, byte stride, and offsets.
 * This is used to correctly bind vertex buffers to the GPU.
 */
class BufferLayout {
public:
    /// Constructs an empty layout (used rarely).
    BufferLayout() = default;

    /**
     * @brief Constructs a layout from a list of BufferElements.
     * 
     * @param elements List of attributes for a vertex.
     */
    BufferLayout(const std::initializer_list<BufferElement> &elements);

    /**
     * @brief Gets the list of all BufferElements in this layout.
     * @return A const reference to the internal vector of elements.
     */
    [[nodiscard]] inline const std::vector<BufferElement> &GetElements() const { return elements; }

    /**
     * @brief Gets the total size in bytes of one vertex (stride).
     * @return The stride in bytes.
     */
    [[nodiscard]] inline uint32_t GetStride() const { return stride; }

private:
    /**
     * @brief Calculates the offset of each element and the total stride.
     * 
     * Called during construction to assign each element’s `offset` and compute total vertex size.
     */
    void CalculateOffsetsAndStride();

private:
    std::vector<BufferElement> elements; ///< Ordered list of vertex attributes.
    uint32_t stride = 0;                 ///< Total size in bytes of one vertex.
};

} // namespace Ebony
