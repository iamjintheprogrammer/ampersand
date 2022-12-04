cmake_minimum_required(VERSION 3.12)
project(ampersand.example.schema
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.schema.table  table.cpp)
add_executable(example.schema.select select.cpp)