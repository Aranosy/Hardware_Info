cmake_minimum_required(VERSION 3.10)

project(hardinf VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include/hardware)
include_directories(${PROJECT_SOURCE_DIR}/include/utils)

add_executable(test src/test.cpp)
