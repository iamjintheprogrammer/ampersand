#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/proto/body.hpp>

namespace ampersand::proto {
    template <typename... Attributes>
    using buffer = meta::meta_object<proto::buffer_body, meta::meta_type<Attributes...>>;
}