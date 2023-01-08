cmake_minimum_required(VERSION 3.12)

project    (ampersand.diopter VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.diopter STATIC
            ../diopter.hpp
            type.hpp
            type_compound.hpp
            type_primitive.hpp
            type_function.hpp
            type.cpp
            type_compound.cpp
            type_primitive.cpp
            type_function.cpp)

set_target_properties(ampersand.diopter PROPERTIES LINKER_LANGUAGE CXX)