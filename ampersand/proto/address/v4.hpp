#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/proto/field.hpp>

namespace ampersand::proto::annotation {
    struct v4          : meta::annotation {};
    struct v4_sender   : meta::annotation {};
    struct v4_receiver : meta::annotation {};
}

namespace ampersand::proto::attribute {
    using v4 
        = meta::attribute<std::uint32_t,
            meta::annotation_set
                <proto::annotation::v4, 
                 proto::annotation::field>>;

    using v4_sender 
        = meta::attribute<std::uint32_t,
            meta::annotation_set
                <proto::annotation::v4_sender, 
                 proto::annotation::field>>;

    using v4_receiver 
        = meta::attribute<std::uint32_t,
            meta::annotation_set
                <proto::annotation::v4_receiver, 
                 proto::annotation::field>>;
}