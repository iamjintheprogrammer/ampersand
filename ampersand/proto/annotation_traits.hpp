#pragma once
#include <type_traits>

#include <ampersand/meta/meta.hpp>
#include <ampersand/proto/annotation.hpp>

namespace ampersand::proto {
    template <typename T> struct                   is_field        : std::false_type {};
    template <>           struct                   is_field<field> : std::true_type  {};
    template <typename T> inline constexpr bool    is_field_v      = is_field::value;

    template <typename T>    struct                is_aligned_field                   : std::false_type {};
    template <std::size_t N> struct                is_aligned_field<aligned_field<N>> : std::true_type  {};
    template <typename T>    inline constexpr bool is_aligned_field_v = is_aligned_field<T>::value;

    template <typename T> struct                    is_remapped                 : std::false_type {};
    template <typename T> struct                    is_remapped<remap_field<T>> : std::true_type  {};
    template <typename T> inline constexpr bool     is_remapped_v = is_remapped<T>::value;
    
    template <typename T> struct                    is_deprecated                   : std::false_type {};
    template <>           struct                    is_deprecated<deprecated_field> : std::true_type  {};
    template <typename T> inline constexpr bool     is_deprecated_v = is_deprecated<T>::value;

    template <typename T> struct                    is_received_size               : std::false_type {};
    template <>           struct                    is_received_size<receive_size> : std::true_type  {};

    template <typename T> struct                    is_send_size            : std::false_type {};
    template <>           struct                    is_send_size<send_size> : std::true_type  {};

    template <typename T>
    struct is_resizable                               : std::false_type {};
    template <typename T, std::size_t Min, std::size_t Max>
    struct is_resizable<resizable_field<T, Min, Max>> : std::true_type  {};

    template <typename T>
    struct has_field_annotation : std::false_type {};

    template <typename T>
    struct has_field_attribute  : std::false_type {};

    template <typename AttrT, typename... Annotations>
    struct has_field_annotation<meta::attribute<AttrT, Annotations...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, is_field>::value
                        != sizeof...(Annotations));
    };

    template <typename... Attribute>
    struct has_field_attribute<meta::meta_type<Attribute...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Attribute...>, has_field_attribute>::value
                        != sizeof...(Attribute));
    };

    template <typename T>
    struct has_aligned_field_annotation : std::false_type {};

    template <typename T>
    struct has_aligned_field_attribute  : std::false_type {};

    template <typename AttrT, typename... Annotations>
    struct has_aligned_field_annotation<meta::attribute<AttrT, Annotations...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, is_aligned_field>::value
                        != sizeof...(Annotations));
    };

    template <typename... Attribute>
    struct has_aligned_field_attribute<meta::meta_type<Attribute...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Attribute...>, has_aligned_field_annotation>::value
                        != sizeof...(Attribute));
    };

    template <typename T>
    struct has_remapped_field_annotation : std::false_type {};

    template <typename T>
    struct has_remapped_field_attribute  : std::false_type {};

    template <typename AttrT, typename... Annotations>
    struct has_remapped_field_annotation<meta::attribute<AttrT, Annotations...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, is_remapped>::value
                        != sizeof...(Annotations));
    };

    template <typename... Attribute>
    struct has_remapped_field_attribute<meta::meta_type<Attribute...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Attribute...>, has_remapped_field_annotation>::value
                        != sizeof...(Attribute));
    };

    template <typename T>
    struct has_deprecated_field_annotation : std::false_type {};

    template <typename T>
    struct has_deprecated_field_attribute  : std::false_type {};

    template <typename AttrT, typename... Annotations>
    struct has_deprecated_field_annotation<meta::attribute<AttrT, Annotations...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, is_deprecated>::value
                        != sizeof...(Annotations));
    };

    template <typename... Attribute>
    struct has_deprecated_field_attribute<meta::meta_type<Attribute...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Attribute...>, has_deprecated_field_annotation>::value
                        != sizeof...(Attribute));
    };

    template <typename T>
    struct has_received_field_annotation : std::false_type {};

    template <typename T>
    struct has_received_field_attribute  : std::false_type {};

    template <typename AttrT, typename... Annotations>
    struct has_received_field_annotation<meta::attribute<AttrT, Annotations...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, is_received_size>::value
                        != sizeof...(Annotations));
    };

    template <typename... Attribute>
    struct has_received_field_attribute<meta::meta_type<Attribute...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Attribute...>, has_received_field_annotation>::value
                        != sizeof...(Attribute));
    };

    template <typename T>
    struct has_send_field_annotation : std::false_type {};

    template <typename T>
    struct has_send_field_attribute : std::false_type {};

    template <typename AttrT, typename... Annotations>
    struct has_send_field_annotation<meta::attribute<AttrT, Annotations...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Annotations...>, is_send_size>::value
                        != sizeof...(Annotations));
    };

    template <typename... Attribute>
    struct has_send_field_attribute<meta::meta_type<Attribute...>> {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<Attribute...>, has_send_field_annotation>::value
                        != sizeof...(Attribute));
    };
}

namespace ampersand::proto::concepts {
    template <typename AnyType> concept            field = has_field_annotation           <AnyType>::value;
    template <typename AnyType> concept remappable_field = has_remapped_field_annotation  <AnyType>::value;
    template <typename AnyType> concept deprecated_field = has_deprecated_field_annotation<AnyType>::value;
    template <typename AnyType> concept    aligned_field = has_aligned_field_annotation   <AnyType>::value;

    template <typename AnyType> concept received_size_field = has_received_field_annotation<AnyType>::value;
    template <typename AnyType> concept     send_size_field =     has_send_field_annotation<AnyType>::value;
}