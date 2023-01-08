#pragma once
#include <type_traits>

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

#define AMPERSAND_DECLARE_META_OPERATOR \
template <typename RhsType>\
constexpr auto operator+  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <add,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator+=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <add_and_store,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator-  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <subtract,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator-=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <subtract_and_store,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator*  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <multiply,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator*=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <multiply_and_store,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator/  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <divide,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator/=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <divide_and_store,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator== (RhsType&& pRhs){\
    return\
        meta_operator\
            <equal,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator!=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <not_equal,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator&&  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <and_with,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator||  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <or_with,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator=  (RhsType&&  pRhs){\
    if constexpr (std::is_lvalue_reference_v<decltype(pRhs)>) {\
        return\
            meta_operator\
                <copy,\
                 meta_operator<verb, Operand...>,\
                 std::remove_reference_t<RhsType>>  (*this, pRhs);\
    }\
    else {\
        return\
            meta_operator\
                <move,\
                 meta_operator<verb, Operand...>,\
                 std::remove_reference_t<RhsType>>  (*this, pRhs);\
    }\
}\
template <typename RhsType>\
constexpr auto operator< (RhsType&&  pRhs){\
    return\
        meta_operator\
            <less_than,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator<=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <less_or_equal,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator>  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <greater_than,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}\
template <typename RhsType>\
constexpr auto operator>=  (RhsType&&  pRhs){\
    return\
        meta_operator\
            <greater_or_equal,\
             meta_operator<verb, Operand...>,\
             std::remove_reference_t<RhsType>>  (*this, pRhs);\
}