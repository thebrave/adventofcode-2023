cmake_minimum_required(VERSION 3.10)

project(AdventOfCode) 

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/_cots/Catch2/extras)
include(CTest)
include(Catch)

add_subdirectory(_cots/Catch2)
add_subdirectory(_commonlib)
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
