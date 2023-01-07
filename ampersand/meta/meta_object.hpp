#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class meta_object;

    template <concepts::meta_type MetaType>
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
        
        auto& operator[] (concepts::attribute auto pAttribute)       { return traits_type::get(_M_Body, pAttribute); }
        
        AMPERSAND_ENABLE_META_OPERATOR
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

    };
}

namespace ampersand::meta::utility {
    template <typename... AnyType>
    struct is_meta_object                        : std::false_type {};
    template <concepts::meta_type MetaType>
    struct is_meta_object<meta_object<MetaType>> : std::true_type  {};
    template <typename... AnyType>
    inline constexpr bool is_meta_object_v = is_meta_object<AnyType...>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType>
    concept meta_object = utility::is_meta_object_v<AnyType...>;
}