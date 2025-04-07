cmake_minimum_required(VERSION 3.29)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)

include(cmakes/CPM.cmake)
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.8")

#glm is a header-only library, so no need to build it.
CPMAddPackage(
        NAME "glm"
        GIT_TAG "0.9.3.2"
        GITHUB_REPOSITORY "icaven/glm"
        DOWNLOAD_ONLY YES
)

add_executable(fumopong src/main.cpp src/glad.c
        include/stb_image.h
        src/stb_image.cpp)
target_include_directories(fumopong PUBLIC include)
target_include_directories(fumopong
        PUBLIC
        $<BUILD_INTERFACE:${glm_SOURCE_DIR}>
)
target_link_libraries(fumopong PRIVATE SDL3::SDL3)



if(WIN32)
    add_custom_command(
            TARGET fumopong POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:fumopong>
            VERBATIM
    )
endif()