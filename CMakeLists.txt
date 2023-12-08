cmake_minimum_required(VERSION 3.10)

project(AdventOfCode) 

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/_cots/Catch2/extras)
include(CTest)
include(Catch)

add_subdirectory(_cots)

# find_program(IWYU_BIN include-what-you-use
#     DOC "Include What You Use")
# if(NOT IWYU_BIN STREQUAL "IWYU_BIN-NOTFOUND")
#     message("iwyu enabled")
#     set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_BIN};-w;-Xiwyu;--verbose=7")
# endif()

add_subdirectory(_commonlib)
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)

add_subdirectory(day08)
