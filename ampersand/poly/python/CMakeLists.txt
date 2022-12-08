cmake_minimum_required(VERSION 3.12)

project    (ampersand.poly.python VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.poly.python STATIC
            describer.hpp
            desc_instruction.hpp
            desc_instruction.cpp)

set_target_properties(ampersand.poly.python PROPERTIES LINKER_LANGUAGE CXX)