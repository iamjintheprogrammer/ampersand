cmake_minimum_required(VERSION 3.12)
project(ampersand.example.extension.mysql
        VERSION 0.1.0
        LANGUAGES CXX)

add_executable(example.extension.mysql.connection
               connection.cpp
               connection.hpp)

add_executable(example.extension.mysql.select        select.cpp)
add_executable(example.extension.mysql.select_parsed select_parsed.cpp)

target_link_libraries(example.extension.mysql.select        PRIVATE ampersand.extension.mysql)
target_link_libraries(example.extension.mysql.select_parsed PRIVATE ampersand.extension.mysql)
target_link_libraries(example.extension.mysql.connection    PRIVATE ampersand.extension.mysql)