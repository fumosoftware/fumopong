cmake_minimum_required(VERSION 3.29.6)
project(libfumo)

set(CMAKE_CXX_STANDARD 23)

add_library(libfumo libfumo/rendering_engine.h libfumo/rendering_engine.cpp)
target_include_directories(libfumo
        PUBLIC
        ${CMAKE_SOURCE_DIR}/libfumo
)

target_link_libraries(libfumo PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(
            TARGET libfumo POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:libfumo>
            VERBATIM
    )
endif()
