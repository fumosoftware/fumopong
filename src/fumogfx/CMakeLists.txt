cmake_minimum_required(VERSION 3.29)
project(fumogfx)

set(CMAKE_CXX_STANDARD 23)

add_library(fumogfx
        api/fumogfx/rendering_device.h
        api/fumogfx/rendering_device.cpp
        src/opengl/glad/glad.h
        src/opengl/glad/glad.c
        src/opengl/glad/KHR/khrplatform.h
        src/opengl/rendering_device.h
        src/opengl/rendering_device.cpp
        src/opengl/rendering_device_context.cpp
        src/opengl/rendering_device_context.h
)
target_include_directories(fumogfx PUBLIC api)
target_include_directories(fumogfx PRIVATE src)
target_include_directories(fumogfx PRIVATE external)
target_link_libraries(fumogfx PRIVATE SDL3::SDL3)
