#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/attribute.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class basic_meta_object;

    template <concepts::meta_type MetaType, typename BodyTrait>
    class basic_meta_object<MetaType, BodyTrait> {
        using __string_view = std::string_view;
              __string_view _M_Name;
        using __body_type = typename BodyTrait::body_type;
              __body_type   _M_Body;
        using      __type = MetaType;
                   __type   _M_Type;

    public:
        using   body_type = __body_type;
        using traits_type = BodyTrait  ;
        using        type = MetaType   ;

        constexpr basic_meta_object
            (concepts::meta_type auto pType, const char* pName) 
                : _M_Type(pType),
                  _M_Name(pName) {}
        constexpr basic_meta_object
            (concepts::meta_type auto pType) 
                : _M_Type(pType) {}
    public:

        body_type&  get_body() { return _M_Body; }
        type&       type_of () { return _M_Type; }
        const char* name    () { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        
        template <typename KeyType>
                                       auto& operator[] (KeyType pKey)                        { return traits_type::get(_M_Body, pKey); }
        
        template <typename... RhsType> auto  operator<  (const basic_meta_object<RhsType...>& pRhs) { return traits_type::less_than    (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator<= (const basic_meta_object<RhsType...>& pRhs) { return traits_type::less_or_equal(_M_Body, pRhs.get_body()); }

        template <typename... RhsType> auto  operator>  (const basic_meta_object<RhsType...>& pRhs) { return traits_type::greater_than    (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator>= (const basic_meta_object<RhsType...>& pRhs) { return traits_type::greater_or_equal(_M_Body, pRhs.get_body()); }

        template <typename... RhsType> auto  operator== (const basic_meta_object<RhsType...>& pRhs) { return traits_type::equal    (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator!= (const basic_meta_object<RhsType...>& pRhs) { return traits_type::not_equal(_M_Body, pRhs.get_body()); }

        template <typename... RhsType> auto  operator=  (const basic_meta_object<RhsType...>&  pRhs) { return traits_type::move     (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator=  (const basic_meta_object<RhsType...>&& pRhs) { return traits_type::move_deep(_M_Body, pRhs.get_body()); }
    };

    template <concepts::primitive MetaType, typename BodyTrait>
    class basic_meta_object<MetaType, BodyTrait> {
        using __string_view = std::string_view;
              __string_view _M_Name;
        using __body_type = typename BodyTrait::body_type;
              __body_type _M_Body;

    public:
        basic_meta_object(const char* pName)
            : _M_Name(pName) {} // For CTAD Support
        basic_meta_object()  {}
    public:
        using body_type   = __body_type;
        using traits_type = BodyTrait;

        body_type&  get_body();
        const char* name    () { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        
                                       auto& operator*  ()                                    { return traits_type::get(_M_Body); }
        
        template <typename... RhsType> auto  operator<  (const basic_meta_object<RhsType...>& pRhs) { return traits_type::less_than    (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator<= (const basic_meta_object<RhsType...>& pRhs) { return traits_type::less_or_equal(_M_Body, pRhs.get_body()); }

        template <typename... RhsType> auto  operator>  (const basic_meta_object<RhsType...>& pRhs) { return traits_type::greater_than    (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator>= (const basic_meta_object<RhsType...>& pRhs) { return traits_type::greater_or_equal(_M_Body, pRhs.get_body()); }

        template <typename... RhsType> auto  operator== (const basic_meta_object<RhsType...>& pRhs) { return traits_type::equal    (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator!= (const basic_meta_object<RhsType...>& pRhs) { return traits_type::not_equal(_M_Body, pRhs.get_body()); }

        template <typename... RhsType> auto  operator=  (const basic_meta_object<RhsType...>&  pRhs) { return traits_type::move     (_M_Body, pRhs.get_body()); }
        template <typename... RhsType> auto  operator=  (const basic_meta_object<RhsType...>&& pRhs) { return traits_type::move_deep(_M_Body, pRhs.get_body()); }
                                       auto  operator=  (MetaType::value_type pRhs)            { traits_type::get(_M_Body) = pRhs; }
    };
}