cmake_minimum_required(VERSION 3.15)
project(SignumFlux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

enable_testing()

find_package(GTest REQUIRED)

add_subdirectory(test)