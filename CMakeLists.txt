cmake_minimum_required(VERSION 3.29)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)

include(cmakes/CPM.cmake)
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.8")

add_executable(fumopong src/main.cpp external/glad/glad.c
        src/rendering/drivers/rendering_context_device_interface.h
        src/rendering/drivers/opengl/window.cpp
        src/rendering/drivers/opengl/window.h
        src/rendering/drivers/window_interface.h
        src/rendering/drivers/opengl/rendering_context_device.cpp
        src/rendering/drivers/opengl/rendering_context_device.h
        src/rendering/rendering_context.cpp
        src/rendering/rendering_context.h
)
target_link_libraries(fumopong PRIVATE SDL3::SDL3)
target_include_directories(fumopong PRIVATE external)

if(WIN32)
    add_custom_command(
            TARGET fumopong POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:fumopong>
            VERBATIM
    )
endif()