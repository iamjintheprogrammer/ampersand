#pragma once
#include <ampersand/proto/annotation_utility.hpp>
#include <ampersand/proto/annotation_traits.hpp>

namespace ampersand::proto {
    template <typename... T>
    struct __buffer_body_size;

    template <typename AttrT, typename... AttrRemaining>
    struct __buffer_body_size<AttrT, AttrRemaining...> {
        static constexpr std::size_t value = []()->std::size_t {
                if constexpr (!has_field_annotation<AttrT>::value)
                    return __buffer_body_size<AttrRemaining...>::value;
                else
                    return 
                        utility::field_size<AttrT>::value
                            + __buffer_body_size<AttrRemaining...>::value;
            }();
    };

    template <typename AttrT>
    struct __buffer_body_size<AttrT> {
        static constexpr std::size_t value = []()->std::size_t {
                if constexpr (!has_field_annotation<AttrT>::value)
                    return 0;
                else
                    return 
                        utility::field_size<AttrT>::value;
            }();
    };

    template <typename... T>
    struct __buffer_offset;

    template <typename T, typename AttrT, typename... AttrRemaining>
    struct __buffer_offset<T, meta::meta_type<AttrT, AttrRemaining...>> {
        static constexpr std::size_t value = []()->std::size_t {
                if constexpr (std::is_same_v<T, AttrT>)
                    return 0;
                if constexpr (!has_field_annotation<AttrT>::value)
                    return __buffer_offset<T, meta::meta_type<AttrRemaining...>>::value;
                else
                    return 
                        utility::field_size<AttrT>::value
                            + __buffer_offset<T, meta::meta_type<AttrRemaining...>>::value;
            }();
    };

    template <typename T, typename AttrT>
    struct __buffer_offset<T, meta::meta_type<AttrT>> {
        static constexpr std::size_t value = []()->std::size_t {
                if constexpr (std::is_same_v<T, AttrT>)
                    return 0;
                else
                    return utility::field_size<AttrT>::value;
            }();
    };
}