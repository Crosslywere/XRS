cmake_minimum_required(VERSION 3.28)

project(xrs VERSION 0.0)

add_library(xrs STATIC
    src/Renderer.cpp
    deps/glad/src/glad.c
)

target_include_directories(xrs PRIVATE
    include
    deps/glad/include
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_target_properties(xrs PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
