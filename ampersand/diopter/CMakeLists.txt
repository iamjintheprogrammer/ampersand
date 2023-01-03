cmake_minimum_required(VERSION 3.12)

project    (ampersand.diopter VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.diopter STATIC
            loop_header.hpp
            loop.hpp
            condition.hpp
            script.hpp
            describer.hpp
            describer_trait.hpp
            symbol.hpp
            symbol.cpp)

set_target_properties(ampersand.diopter PROPERTIES LINKER_LANGUAGE CXX)
add_subdirectory(engine)