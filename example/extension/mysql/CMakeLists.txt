cmake_minimum_required(VERSION 3.12)
project(ampersand.example.extension.mysql
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.extension.mysql.connection
               connection.cpp
               connection.hpp)

add_executable(example.extension.mysql.reader
               reader.cpp
               reader.hpp)

target_link_libraries(example.extension.mysql.reader     PRIVATE ampersand.extension.mysql)
target_link_libraries(example.extension.mysql.connection PRIVATE ampersand.extension.mysql)