cmake_minimum_required(VERSION 3.12)

project    (ampersand.diopter VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.diopter STATIC
            ../diopter.hpp
            function.hpp
            function_method.hpp
            function.cpp
            function_method.cpp
            type.hpp
            type_compound.hpp
            type_compound_attr.hpp
            type_compound_nested.hpp
            type_primitive.hpp
            type_function.hpp
            type_function_argument.hpp
            type.cpp
            type_compound.cpp
            type_compound_attr.cpp
            type_compound_nested.cpp
            type_primitive.cpp
            type_function_argument.cpp
            symbol.hpp
            symbol_result.hpp
            symbol.cpp
            symbol_result.cpp
            syntax/syntax.hpp
            syntax/syntax_element.hpp
            syntax/syntax_element_object.hpp
            syntax/syntax_element_constant.hpp
            syntax/syntax.cpp
            syntax/syntax_element.cpp)

set_target_properties(ampersand.diopter PROPERTIES LINKER_LANGUAGE CXX)