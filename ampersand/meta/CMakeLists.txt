cmake_minimum_required(VERSION 3.12)

project    (ampersand.meta VERSION 0.1.0 LANGUAGES CXX)
add_library(ampersand.meta STATIC
            meta.hpp
            meta_object.hpp
            meta_object_base.hpp
            meta_object_impl.hpp
            attribute.hpp
            action.hpp
            annotation.hpp
            utility/contains.hpp
            utility/trait_concept.hpp
            utility/trait.hpp
            body/raw.hpp
            body/raw_impl.hpp
            body/tuple.hpp
            body/tuple_impl.hpp
            body/tag.hpp
            body/tag_impl.hpp)

set_target_properties(ampersand.meta PROPERTIES LINKER_LANGUAGE CXX)