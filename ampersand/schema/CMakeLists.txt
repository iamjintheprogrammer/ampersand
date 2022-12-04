cmake_minimum_required(VERSION 3.12)

project    (ampersand.schema VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.schema STATIC
            type.hpp
            type_annotation.hpp
            type_traits.hpp
            table.hpp
            table_impl.hpp
            syntax/select.hpp
            syntax/insert.hpp)

set_target_properties(ampersand.schema PROPERTIES LINKER_LANGUAGE CXX)