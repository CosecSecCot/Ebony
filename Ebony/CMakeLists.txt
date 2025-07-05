cmake_minimum_required(VERSION 3.20)

project(Ebony)

add_library(Ebony STATIC
    src/Renderer/OpenGL/OpenGLBuffer.cpp
    src/Renderer/OpenGL/OpenGLFrameBuffer.cpp
    src/Renderer/OpenGL/OpenGLShader.cpp
    src/Renderer/OpenGL/OpenGLVertexArray.cpp
    src/Renderer/Buffer.cpp
    src/Renderer/BufferLayout.cpp
    src/Renderer/FrameBuffer.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Shader.cpp
    src/Renderer/ShaderDataType.h
    src/Renderer/VertexArray.cpp
    src/UI/UIManager.cpp
    src/Utils/FileUtils.cpp
    src/Timer.cpp
    src/Application.cpp
)

add_subdirectory(vendor)

target_include_directories(Ebony PRIVATE
    src
    vendor/GLFW/include
    vendor/Glad/include
    vendor/GLM
    vendor/ImGui
    vendor/ImGui/backends
)

find_package(OpenGL REQUIRED)
target_link_libraries(Ebony PRIVATE glfw glad glm imgui OpenGL::GL)

target_compile_definitions(Ebony PRIVATE INTER_FONT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/inter.ttf")
target_compile_definitions(Ebony PRIVATE ICON_FONT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/arimo.ttf")
target_compile_definitions(Ebony PRIVATE BASIC_FRAG_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/Basic.frag")
target_compile_definitions(Ebony PRIVATE BASIC_VERT_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/Basic.vert")

set_property(TARGET Ebony PROPERTY CXX_STANDARD 17)
