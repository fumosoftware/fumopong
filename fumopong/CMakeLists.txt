cmake_minimum_required(VERSION 3.29.6)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)

add_executable(fumopong fumopong/main.cpp)
target_compile_definitions(fumopong PUBLIC SPDLOG_FMT_EXTERNAL)
target_link_libraries(fumopong PRIVATE spdlog::spdlog fmt::fmt)
target_link_libraries(fumopong PRIVATE fumo)

if(WIN32)
    add_custom_command(
            TARGET fumopong POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy -t $<TARGET_FILE_DIR:fumopong> $<TARGET_RUNTIME_DLLS:fumopong>
            COMMAND_EXPAND_LISTS
    )
endif()
