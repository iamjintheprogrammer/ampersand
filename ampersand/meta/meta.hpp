#pragma once
#include <tuple>
#include <string_view>

#include <ampersand/meta/operator.hpp>

namespace ampersand::meta {
    template <typename... Attributes>
    struct meta_type {
    private:
        using __string_view = std::string_view;
              __string_view _M_Name;

        using __tuple = std::tuple<Attributes...>;
              __tuple _M_Attribute;
    public:
        constexpr meta_type(const char* pName, Attributes... pAttr)
            : _M_Name     (pName),
              _M_Attribute(pAttr...) {  }

        AMPERSAND_ENABLE_META_OPERATOR

        const char* type_name    ()           { return _M_Name.data(); }
        auto&       get_attribute(auto pAttr) { return std::get<decltype(pAttr)>(_M_Attribute); }

    };

    template <>
    struct meta_type<> {
        constexpr meta_type() {}
    };

    template <>
    struct meta_type<std::int8_t> {
        using      value_type =       std::int8_t ;
        using       reference =       std::int8_t&;
        using const_reference = const std::int8_t&;
        using         pointer =       std::int8_t*;
        using   const_pointer = const std::int8_t*;

        constexpr meta_type()           {  }
        constexpr meta_type(value_type) {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::uint8_t> {
        using      value_type =       std::uint8_t;
        using       reference =       std::uint8_t&;
        using const_reference = const std::uint8_t&;
        using         pointer =       std::uint8_t*;
        using   const_pointer = const std::uint8_t*;

        constexpr meta_type()           {  }
        constexpr meta_type(value_type) {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::int16_t> {
        using      value_type =       std::int16_t;
        using       reference =       std::int16_t&;
        using const_reference = const std::int16_t&;
        using         pointer =       std::int16_t*;
        using   const_pointer = const std::int16_t*;

        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::uint16_t> {
        using      value_type =       std::uint16_t;
        using       reference =       std::uint16_t&;
        using const_reference = const std::uint16_t&;
        using         pointer =       std::uint16_t*;
        using   const_pointer = const std::uint16_t*;

        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::int32_t> {
        using      value_type =       std::int32_t;
        using       reference =       std::int32_t&;
        using const_reference = const std::int32_t&;
        using         pointer =       std::int32_t*;
        using   const_pointer = const std::int32_t*;

        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::uint32_t> {
        using      value_type =       std::uint32_t;
        using       reference =       std::uint32_t&;
        using const_reference = const std::uint32_t&;
        using         pointer =       std::uint32_t*;
        using   const_pointer = const std::uint32_t*;

        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::int64_t> {
        using      value_type =       std::int64_t;
        using       reference =       std::int64_t&;
        using const_reference = const std::int64_t&;
        using         pointer =       std::int64_t*;
        using   const_pointer = const std::int64_t*;
        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<std::uint64_t> {
        using      value_type =       std::uint64_t;
        using       reference =       std::uint64_t&;
        using const_reference = const std::uint64_t&;
        using         pointer =       std::uint64_t*;
        using   const_pointer = const std::uint64_t*;

        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<float> {
        using      value_type =       float;
        using       reference =       float&;
        using const_reference = const float&;
        using         pointer =       float*;
        using   const_pointer = const float*;
        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <>
    struct meta_type<double> {
        using      value_type =       double;
        using       reference =       double&;
        using const_reference = const double&;
        using         pointer =       double*;
        using   const_pointer = const double*;

        constexpr meta_type()                        {  }
        constexpr meta_type(value_type)              {  }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <typename... AttributeT>
    meta_type(AttributeT...)->meta_type<AttributeT...>;

    using u8 = meta_type<std::uint8_t>;
    using i8 = meta_type<std::int8_t>;

    using u16 = meta_type<std::uint16_t>;
    using i16 = meta_type<std::int16_t>;

    using u32 = meta_type<std::uint32_t>;
    using i32 = meta_type<std::int32_t>;

    using u64 = meta_type<std::uint64_t>;
    using i64 = meta_type<std::int64_t>;

    using f32 = meta_type<float>;
    using f64 = meta_type<double>;
}

namespace ampersand::meta::utility {
    template <typename... AnyType>
    struct is_primitive_type                      : std::false_type {};
    template <typename MetaType>
    struct is_primitive_type<meta_type<MetaType>> {
        static inline constexpr bool value
            = std::is_integral_v      <MetaType>
            | std::is_floating_point_v<MetaType>;
    };
    template <typename MetaType>
    struct is_primitive_type<const meta_type<MetaType>> {
        static inline constexpr bool value
            = std::is_integral_v      <MetaType>
            | std::is_floating_point_v<MetaType>;
    };

    template <typename... T>
    inline constexpr bool is_primitive_type_v = is_primitive_type<T...>::value;

    template <typename... AnyType>
    struct is_meta_type                              : std::false_type {};
    template <typename... MetaAttribute>
    struct is_meta_type<meta_type<MetaAttribute...>>
        : std::integral_constant
            <bool, !is_primitive_type_v<meta_type<MetaAttribute...>>> {};
    template <typename... MetaAttribute>
    struct is_meta_type<const meta_type<MetaAttribute...>>
        : std::integral_constant
            <bool, !is_primitive_type_v<meta_type<MetaAttribute...>>> {};

    template <typename... T>
    inline constexpr bool is_meta_type_v = is_meta_type<T...>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType> concept meta_type = utility::is_meta_type_v     <AnyType...>;
    template <typename... AnyType> concept primitive = utility::is_primitive_type_v<AnyType...>;
}