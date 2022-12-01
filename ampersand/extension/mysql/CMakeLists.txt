cmake_minimum_required(VERSION 3.12)

project    (ampersand.extension.mysql VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.extension.mysql STATIC
            types.hpp
            types_annotation.hpp
            table.hpp
            table_impl.hpp
            driver.hpp
            driver.cpp
            connection.hpp
            connection.cpp
            connection_base.hpp
            connection_base.cpp)

set_target_properties(ampersand.extension.mysql PROPERTIES LINKER_LANGUAGE CXX)