cmake_minimum_required(VERSION 3.12)
project(ampersand.example.proto
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.proto
               buffer_body.hpp
               main.cpp)