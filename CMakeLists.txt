cmake_minimum_required(VERSION 3.15)
project(SignumFlux)

list(REMOVE_ITEM CMAKE_PREFIX_PATH "/home/landau/anaconda3")
list(REMOVE_ITEM CMAKE_LIBRARY_PATH "/home/landau/anaconda3/lib")
list(REMOVE_ITEM CMAKE_INCLUDE_PATH "/home/landau/anaconda3/include")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SFML_STATIC_LIBRARIES ON)

enable_testing()

find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics)
find_package(GTest REQUIRED)

target_link_libraries(SFML::Graphics)

add_subdirectory(test)