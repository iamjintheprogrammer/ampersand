#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/implement.hpp>

#include <ampersand/proto/buffer.hpp>

namespace ampersand::proto {
namespace annotation       {
    struct on_receive : meta::annotation {};
    struct on_send    : meta::annotation {};
}
namespace handler {
    template <auto Handler>
    using on_receive = meta::method<Handler, meta::annotation_set<on_receive>>;

    template <auto Handler>
    using on_send    = meta::method<Handler, meta::annotation_set<on_receive>>;
}
}