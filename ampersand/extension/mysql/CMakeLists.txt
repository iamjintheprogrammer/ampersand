cmake_minimum_required(VERSION 3.12)

project    (ampersand.extension.mysql VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.extension.mysql STATIC
            types.hpp
            types_annotation.hpp
            table.hpp
            body.hpp
            body_impl.hpp)

set_target_properties(ampersand.extension.mysql PROPERTIES LINKER_LANGUAGE CXX)