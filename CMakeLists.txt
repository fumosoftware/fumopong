cmake_minimum_required(VERSION 3.29)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)

include(cmakes/CPM.cmake)
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.8")

add_executable(fumopong src/main.cpp src/glad.c)
target_include_directories(fumopong PUBLIC include)
target_link_libraries(fumopong PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(
            TARGET fumopong POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:fumopong>
            VERBATIM
    )
endif()