cmake_minimum_required(VERSION 3.20)

project(Ebony)

add_library(Ebony STATIC
    src/Ebony/Application.cpp
    src/Ebony/Application.h
    src/Ebony.h
)

target_include_directories(Ebony PRIVATE
    src
)

set_property(TARGET Ebony PROPERTY CXX_STANDARD 17)
