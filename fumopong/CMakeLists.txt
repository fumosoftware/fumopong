cmake_minimum_required(VERSION 3.29.6)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)

add_executable(fumopong fumopong/main.cpp)
target_compile_definitions(fumopong PUBLIC SPDLOG_FMT_EXTERNAL)
target_link_libraries(fumopong PRIVATE spdlog::spdlog fmt::fmt SDL3::SDL3)
target_link_libraries(fumopong PRIVATE libfumo)

if(WIN32)
    add_custom_command(
            TARGET fumopong POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:fumopong>
            VERBATIM
    )
endif()
