cmake_minimum_required(VERSION 3.20)

project(Ebony)

add_library(Ebony STATIC
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
)

target_link_libraries(Ebony PRIVATE glfw glad)

set_property(TARGET Ebony PROPERTY CXX_STANDARD 17)
