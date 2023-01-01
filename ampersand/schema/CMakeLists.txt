cmake_minimum_required(VERSION 3.12)

project    (ampersand.schema VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.schema STATIC
            schema.hpp
            table.hpp
            table_annotation.hpp)

add_subdirectory(driver)

set_target_properties(ampersand.schema PROPERTIES LINKER_LANGUAGE CXX)