cmake_minimum_required(VERSION 3.12)

project    (ampersand.diopter.engine VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.diopter.engine STATIC
            type.hpp
            type.cpp
            type_impl.hpp
            type_impl.cpp
            object.hpp
            object_impl.hpp
            object.cpp
            object_impl.cpp
            symbol.hpp
            symbol_impl.hpp
            symbol.cpp)

set_target_properties(ampersand.diopter.engine PROPERTIES LINKER_LANGUAGE CXX)