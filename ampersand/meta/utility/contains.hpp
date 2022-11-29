#pragma once
#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::meta::utility {
    template <typename... AnyType>
    struct contains { static constexpr bool value = false; };

    template <typename Target, concepts::annotation... Annotations>
    struct contains<Target, Annotations...> {
        static constexpr bool value 
            = boost::mp11::mp_find
                <boost::mp11::mp_list<Annotations...>, Target>::value
                    != boost::mp11::mp_size<boost::mp11::mp_list<Annotations...>>::value;
    };

    template <typename... AnyType>
    struct contains_if { static constexpr bool value = false; };

    template <typename Predicate, concepts::annotation... Annotations>
    struct contains_if<Predicate, Annotations...> {
        static constexpr bool value
            = boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, Predicate>::value
                        != boost::mp11::mp_size<boost::mp11::mp_list<Annotations...>>::value;
    };

    template <typename... T> inline constexpr bool contains_v    = contains   <T...>::value;
    template <typename... T> inline constexpr bool contains_if_v = contains_if<T...>::value;
}