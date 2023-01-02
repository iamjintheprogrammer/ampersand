cmake_minimum_required(VERSION 3.12)

project    (ampersand.diopter VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.diopter STATIC
            declare.hpp
            describe.hpp
            component.hpp
            component_traits.hpp
            loop.hpp
            scope.hpp
            conditional.hpp)

set_target_properties(ampersand.diopter PROPERTIES LINKER_LANGUAGE CXX)