cmake_minimum_required(VERSION 3.12)

project    (ampersand.extension.mysql VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.extension.mysql STATIC
            driver.hpp
            driver.cpp
            connection.hpp
            connection.cpp
            connection_base.hpp
            connection_base.cpp
            reader.hpp
            reader_iterator.hpp
            reader_impl.hpp
            writer.hpp
            writer_impl.hpp
            parser.hpp
            parser_impl.hpp)

set_target_properties(ampersand.extension.mysql PROPERTIES LINKER_LANGUAGE CXX)