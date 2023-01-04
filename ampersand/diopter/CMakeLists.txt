cmake_minimum_required(VERSION 3.12)

project    (ampersand.diopter VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.diopter STATIC
            ../diopter.hpp
            loop_header.hpp
            loop.hpp
            condition.hpp
            script.hpp
            type.hpp
            type_impl.hpp
            type.cpp
            type_impl.cpp
            symbol.hpp
            symbol.cpp
            object.hpp
            object.cpp
            syntax.hpp
            syntax.cpp
            stack.hpp
            stack.cpp
            scope.hpp
            scope.cpp)

set_target_properties(ampersand.diopter PROPERTIES LINKER_LANGUAGE CXX)