cmake_minimum_required(VERSION 3.20)

project(Ebony)

add_library(Ebony STATIC
    src/Renderer/OpenGL/OpenGLBuffer.cpp
    src/Renderer/OpenGL/OpenGLBuffer.h
    src/Renderer/OpenGL/OpenGLFrameBuffer.cpp
    src/Renderer/OpenGL/OpenGLFrameBuffer.h
    src/Renderer/OpenGL/OpenGLShader.cpp
    src/Renderer/OpenGL/OpenGLShader.h
    src/Renderer/OpenGL/OpenGLVertexArray.cpp
    src/Renderer/OpenGL/OpenGLVertexArray.h
    src/Renderer/Buffer.cpp
    src/Renderer/Buffer.h
    src/Renderer/BufferLayout.cpp
    src/Renderer/BufferLayout.h
    src/Renderer/FrameBuffer.cpp
    src/Renderer/FrameBuffer.h
    src/Renderer/Renderer.cpp
    src/Renderer/Renderer.h
    src/Renderer/Shader.cpp
    src/Renderer/Shader.h
    src/Renderer/ShaderDataType.h
    src/Renderer/VertexArray.cpp
    src/Renderer/VertexArray.h
    src/Utils/FileUtils.cpp
    src/Utils/FileUtils.h
    src/Timer.cpp
    src/Timer.h
    src/Application.cpp
    src/Application.h
    src/Ebony.h
)

add_subdirectory(vendor)

target_include_directories(Ebony PRIVATE
    src
    ./vendor/GLFW/include
    ./vendor/Glad/include
    ./vendor/GLM
    ./vendor/ImGui
    ./vendor/ImGui/backends
)

find_package(OpenGL REQUIRED)
target_link_libraries(Ebony PRIVATE glfw glad glm imgui OpenGL::GL)

target_compile_definitions(Ebony PRIVATE BASIC_FRAG_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/Basic.frag")
target_compile_definitions(Ebony PRIVATE BASIC_VERT_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/Basic.vert")

set_property(TARGET Ebony PROPERTY CXX_STANDARD 17)
