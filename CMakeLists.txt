cmake_minimum_required(VERSION 3.28)

project(xrs VERSION 0.0)

add_library(xrs STATIC
    src/Renderer.cpp
    src/Framebuffer.cpp
    src/Texture.cpp
    deps/glad/src/glad.c
    deps/stb/stb_impl.cpp
)

target_include_directories(xrs PRIVATE
    include
    deps/glad/include
    deps/stb
)

#GLFW subdirectory
add_subdirectory(test/vendor/glfw)
#Testing
add_executable(xrs_test test/test.cpp)
target_link_libraries(xrs_test PRIVATE
    xrs
    glfw
)
target_include_directories(xrs_test PRIVATE
    include
    test/vendor/glfw/include
)
enable_testing()
add_test(NAME xrs_test COMMAND xrs_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_target_properties(xrs PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(xrs_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
