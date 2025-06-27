add_subdirectory(GLFW)
add_subdirectory(Glad)
add_subdirectory(GLM)

# Setting up ImGui
add_library(imgui STATIC
    ImGui/imconfig.h
    ImGui/imgui.cpp
    ImGui/imgui.h
    ImGui/imgui_demo.cpp
    ImGui/imgui_draw.cpp
    ImGui/imgui_internal.h
    ImGui/imgui_tables.cpp
    ImGui/imgui_widgets.cpp
    ImGui/imstb_rectpack.h
    ImGui/imstb_textedit.h
    ImGui/imstb_truetype.h

    ImGui/backends/imgui_impl_glfw.cpp
    ImGui/backends/imgui_impl_glfw.h
    ImGui/backends/imgui_impl_opengl3.cpp
    ImGui/backends/imgui_impl_opengl3.h
)
target_include_directories(imgui PRIVATE
    ImGui
    GLFW/include
)
set_property(TARGET imgui PROPERTY CXX_STANDARD 17)
