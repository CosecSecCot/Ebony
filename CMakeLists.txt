cmake_minimum_required(VERSION 3.20)

project(EbonyProject)

add_executable(ebony-engine main.cpp)

target_include_directories(ebony-engine PRIVATE
    Ebony/src
    Ebony/vendor/GLFW/include
    Ebony/vendor/Glad/include
)

add_subdirectory(Ebony)
target_link_libraries(ebony-engine PRIVATE Ebony)

set_target_properties(ebony-engine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/ebony-engine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/ebony-engine
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/ebony-engine
)

set_property(TARGET ebony-engine PROPERTY CXX_STANDARD 17)
