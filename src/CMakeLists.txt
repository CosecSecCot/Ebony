cmake_minimum_required(VERSION 3.20)

project(Ebony)

add_library(Ebony STATIC
    Ebony/Application.cpp
    Ebony/Application.h
    Ebony.h
)

target_include_directories(Ebony PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_property(TARGET Ebony PROPERTY CXX_STANDARD 17)
