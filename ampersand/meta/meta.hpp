#pragma once
#include <tuple>
#include <string_view>

#include <ampersand/meta/operator.hpp>

namespace ampersand::meta         {
    enum class primitive_category {
        i8 , u8,
        i16, u16,
        i32, u32,
        i64, u64,

        f32, f64,
        any, function, none
    };

    struct none_type {};
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

        const char* type_id() { return _M_Name.data(); }
        template <std::size_t Idx, typename... Attributes> friend auto& get_attribute(meta_type<Attributes...>&);
        template <typename Target, typename... Attributes> friend auto& get_attribute(meta_type<Attributes...>&);

        template <typename... RhsType>
        constexpr auto operator=  (meta_type<RhsType...>& pRhs)  { return meta_operator{ copy{}, *this, pRhs }; }
        template <typename... RhsType>
        constexpr auto operator=  (meta_type<RhsType...>&& pRhs) { return meta_operator{ move{}, *this, pRhs }; }
    };

    template <std::size_t Idx, typename... Attributes> 
    auto& get_attribute(meta_type<Attributes...>& pMeta) {
        return
            std::get<Idx>(pMeta._M_Attribute);
    }

    template <typename Target, typename... Attributes> 
    auto& get_attribute(meta_type<Attributes...>& pMeta) {
        return
            std::get<Target>(pMeta._M_Attribute);
    }

    template <> // Any Type
    struct meta_type<> {
        using      value_type = void;
        using       reference = void;
        using const_reference = void;
        using         pointer = void;
        using   const_pointer = void;

        constexpr meta_type() {  }
        constexpr primitive_category type_id  () { return primitive_category::any; }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <> // Any Type
    struct meta_type<none_type> {
        using      value_type = void;
        using       reference = void;
        using const_reference = void;
        using         pointer = void;
        using   const_pointer = void;

        constexpr meta_type() {  }
        constexpr primitive_category type_id  () { return primitive_category::none; }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
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

        constexpr primitive_category type_id() { return primitive_category::i8; }

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

        constexpr primitive_category type_id() { return primitive_category::u8; }

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

        constexpr primitive_category type_id() { return primitive_category::i16; }

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

        constexpr primitive_category type_id() { return primitive_category::u16; }

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

        constexpr primitive_category type_id() { return primitive_category::i32; }

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

        constexpr primitive_category type_id() { return primitive_category::u32; }

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

        constexpr primitive_category type_id() { return primitive_category::i64; }

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

        constexpr primitive_category type_id() { return primitive_category::u64; }

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

        constexpr primitive_category type_id() { return primitive_category::f32; }

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

        constexpr meta_type()           {  }
        constexpr meta_type(value_type) {  }

        constexpr primitive_category type_id() { return primitive_category::f64; }

    public:
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <typename... AttributeT>
    meta_type(AttributeT...)->meta_type<AttributeT...>;

    using any = meta_type<>;

    using u8  = meta_type<std::uint8_t>;
    using i8  = meta_type<std::int8_t>;

    using u16 = meta_type<std::uint16_t>;
    using i16 = meta_type<std::int16_t>;

    using u32 = meta_type<std::uint32_t>;
    using i32 = meta_type<std::int32_t>;

    using u64 = meta_type<std::uint64_t>;
    using i64 = meta_type<std::int64_t>;

    using f32 = meta_type<float>;
    using f64 = meta_type<double>;

    using any  = meta_type<>;
    using none = meta_type<none_type>;
}

namespace ampersand::meta::utility {
    template <typename AnyType>
    struct is_none_type                       : std::false_type {};
    template <>
    struct is_none_type<meta_type<none_type>> : std::true_type  {};
    template <typename T>
    inline constexpr bool is_none_type_v 
        = is_none_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;

    template <typename AnyType>
    struct is_any_type                       : std::false_type {};
    template <>
    struct is_any_type<meta_type<none_type>> : std::true_type  {};
    template <typename T>
    inline constexpr bool is_any_type_v
        = is_any_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;

    template <typename... AnyType>
    struct is_primitive_type                      : std::false_type {};
    template <typename MetaType>
    struct is_primitive_type<meta_type<MetaType>> {
        static inline constexpr bool value
            = std::is_integral_v      <MetaType>
            | std::is_floating_point_v<MetaType>
            |      is_any_type_v      <MetaType>;
    };

    template <typename T>
    inline constexpr bool is_primitive_type_v 
        = is_primitive_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;

    template <typename... AnyType>
    struct is_compound_type : std::false_type {};
    template <typename... T>
    struct is_compound_type<meta_type<T...>>
        : std::integral_constant<bool, !is_primitive_type_v<meta_type<T...>>> {};
    template <typename T>
    inline constexpr bool is_compound_type_v 
        = is_compound_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;
    
    template <typename... AnyType>
    struct is_meta_type                              : std::false_type {};
    template <typename... MetaAttribute>
    struct is_meta_type<meta_type<MetaAttribute...>> : std::true_type  {};

    template <typename T>
    inline constexpr bool is_meta_type_v 
        = is_meta_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;
}

namespace ampersand::meta::concepts {
    template <typename AnyType> concept meta_type = utility::is_meta_type_v     <AnyType>;
    template <typename AnyType> concept primitive = utility::is_primitive_type_v<AnyType>;
    template <typename AnyType> concept compound  = utility::is_compound_type_v <AnyType>;
}

namespace ampersand::meta {
    template <concepts::meta_type R, concepts::meta_type... Args>
    struct meta_type<R(Args...)> {
    private:
        using string_view_impl = std::string_view;
        using        args_impl = std::tuple<Args...>;
        using      return_impl = R;

        string_view_impl impl_name    ;
               args_impl impl_argument;
             return_impl impl_return  ;

    public:
        using      value_type =       R   (Args...);
        using       reference =       R(&)(Args...);
        using const_reference = const R(&)(Args...);
        using         pointer =       R(*)(Args...);
        using   const_pointer = const R(*)(Args...);

    public:
        constexpr                    meta_type(const char*, R, Args...);
        constexpr                    meta_type(R, Args...);
        constexpr const char*        name     ();
        constexpr primitive_category type_id  ();

        template <typename... InArgs>
        constexpr auto operator()(InArgs...);

        template <std::size_t Idx, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_argument_type(meta_type<RhsR(RhsArgs...)>&);
        template <concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_return_type  (meta_type<RhsR(RhsArgs...)>&);
    };

    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    struct meta_type<C, R(C, Args...)> {
    private:
        using string_view_impl = std::string_view;
        using       class_impl = C;
        using      return_impl = R;
        using        args_impl = std::tuple<Args...>;

              class_impl impl_class   ;
        string_view_impl impl_name    ;
             return_impl impl_return  ;
               args_impl impl_argument;
    public:
        using      class_type =                   C;
        using      value_type =       R   (Args...);
        using       reference =       R(&)(Args...);
        using const_reference = const R(&)(Args...);
        using         pointer =       R(*)(Args...);
        using   const_pointer = const R(*)(Args...);

    public:
        constexpr                    meta_type(const char*, class_type, R, Args...);
        constexpr const char*        name     ();
        constexpr primitive_category type_id  ();

        template <typename... InArgs>
        constexpr auto operator()(InArgs...);

        template <std::size_t Idx, concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_argument_type(meta_type<RhsC, RhsR(RhsC, RhsArgs...)>&);
        template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_return_type  (meta_type<RhsC, RhsR(RhsC, RhsArgs...)>&);
        template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_class_type   (meta_type<RhsC, RhsR(RhsC, RhsArgs...)>&);
    };

    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    struct meta_type<C, R(Args...)> {
    private:
        using string_view_impl = std::string_view;
        using      class_impl = C;
        using     return_impl = R;
        using       args_impl = std::tuple<Args...>;

        string_view_impl impl_name    ;
              class_impl impl_class   ;
             return_impl impl_return  ;
               args_impl impl_argument;

    public:
        using      class_type =                   C;
        using      value_type =       R   (Args...);
        using       reference =       R(&)(Args...);
        using const_reference = const R(&)(Args...);
        using         pointer =       R(*)(Args...);
        using   const_pointer = const R(*)(Args...);

    public:
        constexpr                    meta_type(const char*, class_type, R, Args...);
        constexpr const char*        name     ();
        constexpr primitive_category type_id  ();

        template <typename... InArgs> 
        constexpr auto operator()(InArgs... pArgs);

        template <std::size_t Idx, concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_argument_type(meta_type<RhsC, RhsR(RhsArgs...)>&);
        template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_return_type  (meta_type<RhsC, RhsR(RhsArgs...)>&);
        template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
        friend auto get_class_type   (meta_type<RhsC, RhsR(RhsArgs...)>&);
    };

    template <std::size_t Idx, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_argument_type
            (meta_type<RhsR(RhsArgs...)>& pMetaType) {
        return std::get<Idx>(pMetaType.impl_argument);
    }

    template <concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_return_type
            (meta_type<RhsR(RhsArgs...)>& pMetaType) {
        return pMetaType.impl_return;
    }

    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_argument_type
            (meta_type<RhsC, RhsR(RhsC, RhsArgs...)>& pMetaType) {
        return std::get<Idx>(pMetaType.impl_argument);
    }

    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_return_type
            (meta_type<RhsC, RhsR(RhsC, RhsArgs...)>& pMetaType) {
        return pMetaType.impl_return;
    }

    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_class_type
            (meta_type<RhsC, RhsR(RhsC, RhsArgs...)>& pMetaType) {
        return pMetaType.impl_class;
    }

    template <std::size_t Idx, concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_argument_type
            (meta_type<RhsC, RhsR(RhsArgs...)>& pMetaType) {
        return std::get<Idx>(pMetaType.impl_argument);
    }
    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto
        get_return_type
            (meta_type<RhsC, RhsR(RhsArgs...)>& pMetaType) {
        return pMetaType.impl_return;
    }
    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    auto 
        get_class_type
            (meta_type<RhsC, RhsR(RhsArgs...)>& pMetaType) {
        return pMetaType.impl_class;
    }

    template <concepts::meta_type R, concepts::meta_type... Args>
    template <typename... InArgs>
    constexpr auto
        meta_type<R(Args...)>::operator()
            (InArgs... pArgs) {
        return
            meta_operator
                { invoke{}, *this, pArgs... };
    }

    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    template <typename... InArgs>
    constexpr auto
        meta_type<RhsC, RhsR(RhsC, RhsArgs...)>::operator()
            (InArgs... pArgs) {
        return
            meta_operator
                { invoke_method{}, *this, impl_class, pArgs... };

    }

    template <concepts::meta_type RhsC, concepts::meta_type RhsR, concepts::meta_type... RhsArgs>
    template <typename... InArgs>
    constexpr auto
        meta_type<RhsC, RhsR(RhsArgs...)>::operator()
            (InArgs... pArgs) {
        return
            meta_operator
                { invoke_static_method{}, *this, impl_class, pArgs... };
    }

    template <concepts::meta_type R, concepts::meta_type... Args>
    constexpr
        meta_type<R(Args...)>::meta_type
            (const char* pName, R pReturn, Args... pArgs)
                : impl_name    (pName)   ,
                  impl_argument(pArgs...),
                  impl_return  (pReturn) {}

    template <concepts::meta_type R, concepts::meta_type... Args>
    constexpr
        meta_type<R(Args...)>::meta_type
            (R pReturn, Args... pArgs)
                : impl_name    (nullptr) ,
                  impl_argument(pArgs...),
                  impl_return  (pReturn) {  }

    template <concepts::meta_type R, concepts::meta_type... Args>
    constexpr const char*
        meta_type<R(Args...)>::name() {
            return impl_name.data();
    }

    template <concepts::meta_type R, concepts::meta_type... Args>
    constexpr primitive_category
        meta_type<R(Args...)>::type_id() {
            return primitive_category::function;
    }

    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    constexpr
        meta_type<C, R(C, Args...)>::meta_type
            (const char* pName, class_type pClass, R pReturn, Args... pArgs)
                : impl_name    (pName)   ,
                  impl_argument(pArgs...),
                  impl_class   (pClass)  ,
                  impl_return  (pReturn) {  }


    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    constexpr const char*
        meta_type<C, R(C, Args...)>::name() {
            return impl_name.data();
    }

    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    constexpr primitive_category
        meta_type<C, R(C, Args...)>::type_id() {
            return primitive_category::function;
    }


    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    constexpr
        meta_type<C, R(Args...)>::meta_type
            (const char* pName, class_type pClass, R pReturn, Args... pArgs)
                : impl_name    (pName)  ,
                  impl_class   (pClass) ,
                  impl_return  (pReturn),
                  impl_argument(pArgs...) {}

    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    constexpr const char*
        meta_type<C, R(Args...)>::name() {
            return impl_name.data();
    }

    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    constexpr primitive_category
        meta_type<C, R(Args...)>::type_id() {
            return primitive_category::function;
    }
}

namespace ampersand::meta::utility {
    template <typename... AnyType>
    struct is_function_type                              : std::false_type { };
    template <concepts::meta_type R, concepts::meta_type... Args>
    struct is_function_type<meta_type<R(Args...)>>       : std::true_type  { };
    template <typename T>
    inline constexpr bool is_function_type_v
        = is_function_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;

    template <typename AnyType>
    struct is_method_type                                 : std::false_type { };
    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    struct is_method_type<meta_type<C, R(C, Args...)>>    : std::true_type  { };
    template <typename T>
    inline constexpr bool is_method_type_v
        = is_method_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;

    template <typename AnyType>
    struct is_static_method_type                           : std::false_type { };
    template <concepts::meta_type C, concepts::meta_type R, concepts::meta_type... Args>
    struct is_static_method_type<meta_type<C, R(Args...)>> : std::true_type  { };
    template <typename T>
    inline constexpr bool is_static_method_type_v
        = is_static_method_type
            <std::remove_reference_t<std::remove_const_t<T>>>::value;
}

namespace ampersand::meta::concepts {
    template <typename AnyType>
    concept function_type      = utility::is_function_type_v     <AnyType>;
    template <typename AnyType>
    concept method_type        = utility::is_method_type_v       <AnyType>;
    template <typename AnyType>
    concept static_method_type = utility::is_static_method_type_v<AnyType>;
}