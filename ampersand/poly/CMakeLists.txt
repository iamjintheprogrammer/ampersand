cmake_minimum_required(VERSION 3.12)

project    (ampersand.poly VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.poly STATIC
            poly_module.hpp
            poly_module.cpp
            poly_object.hpp
            poly_any.hpp
            poly_any.cpp
            instruction.hpp
            instruction_verb.hpp
            instruction.cpp
            decoder.hpp
            decoder.cpp
            operand.hpp
            operand.cpp
            declare.hpp
            declare.cpp
            fetch.hpp
            fetch.cpp)

set_target_properties(ampersand.poly PROPERTIES LINKER_LANGUAGE CXX)
add_subdirectory(python)