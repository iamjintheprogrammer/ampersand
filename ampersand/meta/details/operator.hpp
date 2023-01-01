#pragma once

#define AMPERSAND_ENABLE_META_OPERATOR \
        template <typename RhsType> \
        constexpr auto operator<  (RhsType&& pRhs) { return meta_operator { less_than{}    , *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator<= (RhsType&& pRhs) { return meta_operator { less_or_equal{}, *this, pRhs }; }\
        template <typename RhsType> \
        constexpr auto operator>  (RhsType&& pRhs) { return meta_operator { greater_than{}    , *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator>= (RhsType&& pRhs) { return meta_operator { greater_or_equal{}, *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator== (RhsType&& pRhs) { return meta_operator { equal{}    , *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator!= (RhsType&& pRhs) { return meta_operator { not_equal{}, *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator+  (RhsType&& pRhs) { return meta_operator{ add{}    , *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator+= (RhsType&& pRhs) { return meta_operator{ add_and_store{}, *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator-  (RhsType&& pRhs) { return meta_operator{ subtract{}          , *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator-= (RhsType&& pRhs) { return meta_operator{ subtract_and_store{}, *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator*  (RhsType&& pRhs) { return meta_operator{ multiply {}    ,* this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator*= (RhsType&& pRhs) { return meta_operator{ multiply_and_store{}, *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator/  (RhsType&& pRhs) { return meta_operator{ divide{}    , *this, pRhs }; }\
        template <typename RhsType>\
        constexpr auto operator/= (RhsType&& pRhs) { return meta_operator{ divide_and_store{}, *this, pRhs }; }\
        template <typename... RhsType>\
        constexpr auto operator=  (meta_type<RhsType...>& pRhs)  { return meta_operator{ copy{}, *this, pRhs }; }\
        template <typename... RhsType>\
        constexpr auto operator=  (meta_type<RhsType...>&& pRhs) { return meta_operator{ move{}, *this, pRhs }; }