cmake_minimum_required(VERSION 3.12)
project(ampersand.example.meta
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.meta.attribute attribute.cpp)
add_executable(example.meta.body      body.cpp)