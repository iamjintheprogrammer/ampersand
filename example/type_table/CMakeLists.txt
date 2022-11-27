cmake_minimum_required(VERSION 3.12)

project(ampersand.example.type_table
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.type_table
               push.hpp
               pop.hpp
               main.cpp
               pop.cpp
               push.cpp)