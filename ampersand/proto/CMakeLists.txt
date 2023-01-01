cmake_minimum_required(VERSION 3.12)

project    (ampersand.proto VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.proto STATIC
            format.hpp)

set_target_properties(ampersand.proto PROPERTIES LINKER_LANGUAGE CXX)