cmake_minimum_required(VERSION 3.12)
project(ampersand.example.meta
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.meta.type     meta_type.cpp)
add_executable(example.meta.operator meta_operator.cpp)
add_executable(example.meta.script   meta_script.cpp)