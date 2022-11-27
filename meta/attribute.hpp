#pragma once
#include <type_traits>
#include <type_table/all.hpp>

namespace ampersand::meta {
    struct attribute {};
    
    template <typename T>
    inline constexpr bool is_attribute_v = std::is_base_of_v<attribute, T>;
    
    template <typename... T>
    using attribute_set = type_table::type_table<T...>;

    template <typename... T>
    struct has_attribute { 
        static constexpr bool value = false; 
    };

    template <typename T, typename... Attr>
    struct has_attribute<T, attribute_set<Attr...>> {
        static constexpr bool value
            = is_attribute_v<T> &&
              type_table::contains_of_v<T, attribute_set<Attr...>>;
    };

    template <typename... T>
    inline constexpr bool has_attribute_v = has_attribute<T...>::value;

    template <typename... T>
    struct push_attribute;

    template <typename T, typename... Attr>
    struct push_attribute<T, attribute_set<Attr...>> {
        using type = type_table::push_back_t<T, attribute_set<Attr...>>;
    };

    template <typename... T>
    using push_attribute_t = typename push_attribute<T...>::type;

    template <typename... T>
    struct pop_attribute;

    template <typename... Attr>
    struct pop_attribute<attribute_set<Attr...>> {
        using type = typename type_table::pop_back_t<attribute_set<Attr...>>::type;
    };

    template <typename... T>
    using pop_attribute_t = typename pop_attribute<T...>::type;
}