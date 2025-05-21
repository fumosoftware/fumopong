cmake_minimum_required(VERSION 3.29.6)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)


add_executable(fumopong src/main.cpp)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.2.0")
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.14")
CPMAddPackage("gh:gabime/spdlog#v1.15.3")
target_compile_definitions(fumopong PUBLIC SPDLOG_FMT_EXTERNAL)
target_link_libraries(fumopong spdlog::spdlog fmt::fmt SDL3::SDL3)

if(WIN32)
    add_custom_command(
            TARGET fumopong POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:fumopong>
            VERBATIM
    )
endif()