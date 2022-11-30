#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/proto/body.hpp>

namespace ampersand::proto {
    template <typename... Attributes>
    using buffer = meta::meta_object<proto::buffer_body, meta::meta_type<Attributes...>>;

   template <typename... Attributes>
   constexpr auto make_buffer(Attributes&&...) {
       return buffer
           <std::remove_const_t
                <std::remove_reference_t<Attributes>>...>{};
   }
}