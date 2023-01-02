cmake_minimum_required(VERSION 3.12)

project    (ampersand.meta VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.meta STATIC
            ../meta.hpp
            meta.hpp
            meta_object.hpp
            attribute.hpp
            annotation.hpp
            operator.hpp
            verb.hpp
            body_traits.hpp
            body_traits_impl.hpp
            operator_impl.hpp)

set_target_properties(ampersand.meta PROPERTIES LINKER_LANGUAGE CXX)