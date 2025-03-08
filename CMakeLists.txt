cmake_minimum_required(VERSION 3.20)

project(EbonyProject)

add_executable(demo main.cpp)

target_include_directories(demo PRIVATE src)

add_subdirectory(src)
target_link_libraries(demo PRIVATE Ebony)

set_target_properties(demo PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/demo
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/demo
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/demo
)

set_property(TARGET demo PROPERTY CXX_STANDARD 17)
