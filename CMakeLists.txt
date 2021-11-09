cmake_minimum_required(VERSION 3.0)
project(CARGS)

set(CMAKE_CXX_STANDARD 11)
include_directories(src)

add_library(CARGS src/CArgs.cpp)

add_executable(BASE test/base/main.cpp)
target_link_libraries(BASE CARGS)

add_executable(MODE test/mode/main.cpp)
target_link_libraries(MODE CARGS)
