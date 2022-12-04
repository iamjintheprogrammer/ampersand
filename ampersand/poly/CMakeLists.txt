cmake_minimum_required(VERSION 3.12)

project    (ampersand.poly VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.poly STATIC
            impl.hpp
            impl_details.hpp
            traits.hpp
            traits_details.hpp)

set_target_properties(ampersand.poly PROPERTIES LINKER_LANGUAGE CXX)