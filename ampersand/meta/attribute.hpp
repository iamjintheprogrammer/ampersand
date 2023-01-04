#pragma once
#include <string_view>

#include <ampersand/meta/annotation.hpp>
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/operator.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class attribute;

    template <concepts::meta_type MetaType, concepts::annotation... Annotation>
    class attribute<MetaType, Annotation...> {
        using __string_view = std::string_view;
              __string_view _M_Name;

        using __tuple = std::tuple<Annotation...>;
              __tuple       _M_Annotation;

        using __meta  = MetaType;
              __meta&       _M_Meta;
    public:
        using value_type = MetaType;
        constexpr attribute
            (const char*   pName,
             MetaType&     pMetaType,
             Annotation... pAnnotation) : _M_Name      (pName)         ,
                                          _M_Annotation(pAnnotation...),
                                          _M_Meta      (pMetaType)     {  }

        const value_type& type() { return _M_Meta; }
        const char*       name() { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }

        template <concepts::annotation AnnotType> 
        auto operator[] (AnnotType) { return std::get<AnnotType>(_M_Annotation); }

        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <concepts::meta_type MetaType>
    class attribute<MetaType> {
        using __string_view = std::string_view;
              __string_view _M_Name;
        using __meta  = MetaType;
              __meta&       _M_Meta;
    public:
        using value_type = MetaType;
        constexpr attribute(const char* pName, MetaType& pMetaType)
            : _M_Name(pName),
              _M_Meta(pMetaType) {} // For CTAD Support

        const value_type& type() { return _M_Meta; }
        const char*       name() { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }

        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <concepts::primitive MetaType, concepts::annotation... Annotation>
    class attribute<MetaType, Annotation...> {
        using __string_view = std::string_view;
              __string_view _M_Name;
        using __tuple = std::tuple<Annotation...>;
              __tuple       _M_Annotation;
    public:
        using value_type = MetaType;
        constexpr attribute
            (const char* pName, Annotation... pAnnotation)
                : _M_Name      (pName),
                  _M_Annotation(pAnnotation) {}// For CTAD Support

        const char*      name() { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        const value_type type() { return value_type {}; }
        template <concepts::annotation Annot> auto get_annotation(Annot) { return std::get<Annot>(_M_Annotation); }

        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <concepts::primitive MetaType>
    class attribute<MetaType> {
        using __string_view = std::string_view;
              __string_view _M_Name;
    public:
        using value_type = MetaType;
        constexpr attribute(const char* pName)
            : _M_Name(pName) {} // For CTAD Support

        const char*      name() { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        const value_type type() { return value_type{}; }
        
        AMPERSAND_ENABLE_META_OPERATOR
    };

    template <concepts::meta_type MetaType, concepts::annotation... Annotation>
    attribute(MetaType, Annotation...) -> attribute<MetaType, Annotation...>;
}

namespace ampersand::meta::utility {
    template <typename... AnyType> struct is_attribute                      : std::false_type {};
    template <typename... Types>   struct is_attribute<attribute<Types...>> : std::true_type  {};
    template <typename... AnyType> inline constexpr bool is_attribute_v = is_attribute<AnyType...>::value;

    template <typename... AnyType>
    struct is_primitive_attribute                                 : std::false_type {};
    template <concepts::primitive Type, typename... Annotation>
    struct is_primitive_attribute<attribute<Type, Annotation...>> : std::true_type  {};
    template <typename... AnyType>
    inline constexpr bool is_primitive_attribute_v = is_primitive_attribute<AnyType...>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType>
    concept           attribute = utility::is_attribute_v<AnyType...>;
    template <typename... AnyType>
    concept primitive_attribute = utility::is_primitive_attribute_v<AnyType...>;
}