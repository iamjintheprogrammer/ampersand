#pragma once
#include <ampersand/define_constexpr.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/proto/field.hpp>

namespace ampersand::proto {
    template <typename... T>
    struct buffer_size;

    template <typename... Attr>
    struct buffer_size<meta::meta_type<Attr...>> {
        static constexpr std::size_t value = []() { 
            return
                (((meta::have_annotation<proto::annotation::field, typename Attr::annotations>)
                    ? sizeof(typename Attr::attribute_type)
                        : 0) + ...);
        }();
    };

    template <typename... T>
    struct buffer_offset;

    template <typename... T>
    struct __buffer_offset;

    template <typename Target, typename Attr, typename... AttributeSet>
    struct __buffer_offset<Target, Attr, AttributeSet...> {
        static constexpr std::size_t value
            = (std::is_same_v<Target, Attr>)
                ? 0
                : ((meta::have_annotation<proto::annotation::field, typename Attr::annotations>)
                    ? (__buffer_offset<Target, AttributeSet...>::value + sizeof(typename Attr::attribute_type))
                    :  __buffer_offset<Target, AttributeSet...>::value);
    };

    template <typename Target, typename Attr>
    struct __buffer_offset<Target, Attr> {
        static constexpr std::size_t value = (std::is_same_v<Target, Attr>) ? 0 : -1;
    };

    template <typename Attribute, typename... Attr>
    struct buffer_offset<Attribute, meta::meta_type<Attr...>> {
        static constexpr std::size_t value
            = __buffer_offset<Attribute, Attr...>::value;
    };

    template <typename... Attr>
    inline constexpr std::size_t buffer_offset_v = buffer_offset<Attr...>::value;

    template <typename... Attr>
    inline constexpr std::size_t buffer_size_v = buffer_size<Attr...>::value;

    template <typename... T>
    struct buffer;

    template <typename... Attr>
    class buffer<meta::meta_type<Attr...>> {
    public:
        using raw_buffer_type = char[buffer_size_v<meta::meta_type<Attr...>>];
        using meta_type       = meta::meta_type<Attr...>;

        buffer(const meta_type&) : _M_Base() {}
        buffer()                             {}

        template <typename Attribute>
        constexpr typename Attribute::attribute_type&
            operator[](Attribute) {
                return
                    *reinterpret_cast<typename Attribute::attribute_type*>
                        (&_M_Base[buffer_offset_v<Attribute, meta::meta_type<Attr...>>]);
        }
    private:
        raw_buffer_type _M_Base;
    };

    template <typename... Attr>
    buffer(meta::meta_type<Attr...>)->buffer<meta::meta_type<Attr...>>;
}