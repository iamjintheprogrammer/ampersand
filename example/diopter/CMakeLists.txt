cmake_minimum_required(VERSION 3.12)
project(ampersand.example.diopter
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable       (example.diopter.type type.cpp)
target_link_libraries(example.diopter.type PRIVATE ampersand.diopter)