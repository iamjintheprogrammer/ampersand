cmake_minimum_required(VERSION 3.12)

project    (ampersand.extension.json VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.extension.json STATIC
            types.hpp
            reader.hpp
            reader_impl.hpp
            writer.hpp
            writer_impl.hpp)

set_target_properties(ampersand.extension.json PROPERTIES LINKER_LANGUAGE CXX)