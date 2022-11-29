#pragma once
#include <ampersand/meta/basic_object.hpp>
#include <ampersand/meta/raw.hpp>

namespace ampersand::meta {
    template <typename MetaT>
    using raw_object = basic_object<raw_body, MetaT>;
}