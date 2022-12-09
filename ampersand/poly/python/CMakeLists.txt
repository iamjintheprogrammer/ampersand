cmake_minimum_required(VERSION 3.12)

project    (ampersand.poly.python VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.poly.python STATIC
            describer.hpp
            describer.cpp
            describer_unit.hpp
            describer_unit.cpp)

set_target_properties(ampersand.poly.python PROPERTIES LINKER_LANGUAGE CXX)