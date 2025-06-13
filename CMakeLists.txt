cmake_minimum_required(VERSION 3.29.6)
project(fumopong)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.2.0")
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.14")
CPMAddPackage("gh:gabime/spdlog#v1.15.3")

add_subdirectory(libfumo)
add_subdirectory(fumopong)