cmake_minimum_required(VERSION 3.12)
project(ampersand
        VERSION 0.1.0
        LANGUAGES CXX)

add_subdirectory   (submodule/mp11)
add_subdirectory   (submodule/jsoncpp)
set                (CMAKE_CXX_STANDARD 20)

option(BUILD_EXAMPLES ON)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/submodule/mp11/include)
include_directories(${CMAKE_SOURCE_DIR}/submodule/jsoncpp/include)

add_subdirectory(ampersand/proto)
add_subdirectory(ampersand/meta)

add_subdirectory(ampersand/extension/mysql)
add_subdirectory(ampersand/extension/json)

if(BUILD_EXAMPLES)
        add_subdirectory(example/proto)
        add_subdirectory(example/meta)
        add_subdirectory(example/extension/mysql)
        add_subdirectory(example/extension/json)
endif()