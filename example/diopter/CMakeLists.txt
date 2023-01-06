cmake_minimum_required(VERSION 3.12)
project(ampersand.example.diopter
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable       (example.diopter.type   type.cpp)
add_executable       (example.diopter.syntax syntax.cpp)
add_executable       (example.diopter.script script.cpp)

target_link_libraries(example.diopter.type   PRIVATE ampersand.diopter)
target_link_libraries(example.diopter.syntax PRIVATE ampersand.diopter)
target_link_libraries(example.diopter.script PRIVATE ampersand.diopter)