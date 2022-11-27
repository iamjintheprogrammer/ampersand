#pragma once
#include <type_traits>
#include <type_table/all.hpp>

namespace ampersand::meta {
    struct attribute {};
    template <typename T>
    inline constexpr bool is_attribute_v = std::is_base_of_v<attribute, T>;
    
    template <typename... T>
    using attribute_set = type_table::type_table<T...>;
}