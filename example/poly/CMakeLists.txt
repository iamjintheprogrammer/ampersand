cmake_minimum_required(VERSION 3.12)
project(ampersand.example.poly
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable       (example.poly.any any.cpp)
target_link_libraries(example.poly.any ampersand.poly ampersand.poly.python)