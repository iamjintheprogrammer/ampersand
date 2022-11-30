cmake_minimum_required(VERSION 3.12)
project(ampersand
        VERSION 0.1.0
        LANGUAGES CXX)

add_subdirectory   (submodule/mp11)
set                (CMAKE_CXX_STANDARD 20)

option(BUILD_EXAMPLES ON)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/submodule/mp11/include)

add_subdirectory(ampersand/proto)
add_subdirectory(ampersand/meta)

add_subdirectory(ampersand/extension/mysql)

if(BUILD_EXAMPLES)
        add_subdirectory(example/proto)
        add_subdirectory(example/meta)
endif()