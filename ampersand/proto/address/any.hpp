#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/proto/field.hpp>

namespace ampersand::proto::annotation {
    struct any_address          : meta::annotation {};
    struct any_receiver_address : meta::annotation {};
    struct any_sender_address   : meta::annotation {};
}

namespace ampersand::proto::attribute {
    template <typename AddrT>
    using any_address = meta::attribute 
                            <AddrT, meta::annotation_set
                                <annotation::any_address, annotation::field>>;
    
    template <typename AddrT>
    using any_receiver_address = meta::attribute 
                                    <AddrT, meta::annotation_set
                                        <annotation::any_address         ,
                                         annotation::any_receiver_address,
                                         annotation::field>>;
    
    template <typename AddrT>
    using any_receiver_address = meta::attribute 
                                    <AddrT, meta::annotation_set
                                        <annotation::any_address         ,
                                         annotation::any_receiver_address,
                                         annotation::field>>;
}