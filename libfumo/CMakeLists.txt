cmake_minimum_required(VERSION 3.29.6)
project(fumo)

set(CMAKE_CXX_STANDARD 23)

add_library(fumo SHARED libfumo/rendering_engine.h libfumo/rendering_engine.cpp
        libfumo/details/opengl/rendering_engine_opengl.cpp
        libfumo/details/opengl/rendering_engine_opengl.h
        libfumo/rendering_window.cpp
        libfumo/rendering_window.h
        libfumo/details/opengl/rendering_window_opengl.cpp
        libfumo/details/opengl/rendering_window_opengl.h)

target_include_directories(fumo
        PUBLIC
        ${CMAKE_SOURCE_DIR}/libfumo
)

target_link_libraries(fumo PRIVATE SDL3::SDL3-shared)

if(WIN32)
    add_custom_command(
            TARGET fumo POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy -t $<TARGET_FILE_DIR:fumo> $<TARGET_RUNTIME_DLLS:fumo>
            COMMAND_EXPAND_LISTS
    )
endif()
