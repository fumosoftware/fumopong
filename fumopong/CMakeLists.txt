cmake_minimum_required(VERSION 3.29.6)
project(fumopong)

set(CMAKE_CXX_STANDARD 23)

add_executable(fumopong fumopong/main.cpp)
target_compile_definitions(fumopong PUBLIC SPDLOG_FMT_EXTERNAL)
target_link_libraries(fumopong PRIVATE spdlog::spdlog fmt::fmt)
target_link_libraries(fumopong PRIVATE libfumo)
