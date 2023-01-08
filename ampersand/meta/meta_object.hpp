#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class meta_object;

    template <concepts::compound MetaType>
    class meta_object<MetaType> {
        using __string_view = std::string_view;
              __string_view _M_Name;
        using      __type = MetaType;
                   __type   _M_Type;

    public:
        using type = MetaType   ;
\
        constexpr meta_object
            (concepts::meta_type auto pObjectType,
             const char*              pObjectName) : _M_Type(pObjectType),
                                                     _M_Name(pObjectName) { }

        constexpr meta_object
            (concepts::meta_type auto pObjectType) : _M_Type(pObjectType),
                                                     _M_Name(nullptr)     { }
    public:
        type&       type_of() { return _M_Type; }
        const char* name   () { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        
        AMPERSAND_ENABLE_META_OPERATOR

        template <typename... RhsType>
        constexpr auto operator=  (meta_object<RhsType...>&  pRhs) { return meta_operator{ copy{}, *this, pRhs }; }
        template <typename... RhsType>
        constexpr auto operator=  (meta_object<RhsType...>&& pRhs) { return meta_operator{ move{}, *this, pRhs }; }
    };

    template <concepts::primitive MetaType>
    class meta_object<MetaType> {
        using __string_view = std::string_view;
              __string_view _M_Name;

    public:
        meta_object(const char* pName) : _M_Name(pName) {} // For CTAD Support
        meta_object()                                   {}
    public:
        using type = MetaType;
        const char* name   () { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        type        type_of() { return type{}; }

        AMPERSAND_ENABLE_META_OPERATOR

        template <typename... RhsType>
        constexpr auto operator=  (meta_object<RhsType...>&  pRhs) { return meta_operator{ copy{}, *this, pRhs }; }
        template <typename... RhsType>
        constexpr auto operator=  (meta_object<RhsType...>&& pRhs) { return meta_operator{ move{}, *this, pRhs }; }
    };

    template <>
    class meta_object<none> {
        using __string_view = std::string_view;
              __string_view _M_Name;

    public:
        meta_object() {}
    public:
        using type = none;
        type        type_of() { return type{}; }
    };
}

namespace ampersand::meta::utility {
    template <typename... AnyType>
    struct is_meta_object                        : std::false_type {};
    template <concepts::meta_type MetaType>
    struct is_meta_object<meta_object<MetaType>> : std::true_type  {};
    template <typename AnyType>
    inline constexpr bool is_meta_object_v 
        = is_meta_object<std::remove_reference_t<std::remove_const_t<AnyType>>>::value;
    
    template <typename AnyType>
    struct is_primitive_object                        : std::false_type {};
    template <concepts::primitive MetaType>
    struct is_primitive_object<meta_object<MetaType>> : std::true_type  {};
    template <typename AnyType>
    inline constexpr bool is_primitive_object_v 
        = is_primitive_object<std::remove_reference_t<std::remove_const_t<AnyType>>>::value;

    template <typename AnyType>
    struct is_compound_object
        : std::integral_constant
            <bool, 
             is_meta_object_v<AnyType> 
         && !is_primitive_object_v<AnyType>> {};
    template <typename AnyType>
    inline constexpr bool is_compound_object_v
        = is_compound_object<std::remove_reference_t<std::remove_const_t<AnyType>>>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType>
    concept meta_object = utility::is_meta_object_v          <AnyType...>;
    template <typename... AnyType>
    concept primitive_object = utility::is_primitive_object_v<AnyType...>;
    template <typename... AnyType>
    concept  compound_object = utility::is_compound_object_v <AnyType...>;
}