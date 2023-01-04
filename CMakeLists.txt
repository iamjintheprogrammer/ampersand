cmake_minimum_required(VERSION 3.12)
project(ampersand
        VERSION 0.1.0
        LANGUAGES CXX)

set                (CMAKE_CXX_STANDARD 20)
set                (CMAKE_C_STANDARD   11)

option(AMPERSAND_BUILD_EXAMPLES ON)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(ampersand/meta)
add_subdirectory(ampersand/diopter)

if(AMPERSAND_BUILD_EXAMPLES)
        add_subdirectory(example/meta)
        add_subdirectory(example/diopter)
endif()