cmake_minimum_required(VERSION 3.12)
project(ampersand
        VERSION 0.1.0
        LANGUAGES CXX)

set                (CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(example/type_table)
add_subdirectory(example/meta)