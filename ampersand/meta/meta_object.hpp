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

        template <typename... InitArgs>
        constexpr basic_meta_object
            (concepts::meta_type auto pObjectType,
             const char*              pObjectName,
             InitArgs&&...            pObjectArgs) : _M_Type(pObjectType),
                                                     _M_Name(pObjectName) { 
            traits_type::construct
                (_M_Body    ,
                 pObjectName,
                 std::forward<InitArgs>(pObjectArgs)...);
        }

        template <typename... InitArgs>
        constexpr basic_meta_object
            (concepts::meta_type auto pObjectType,
             InitArgs&&...            pObjectArgs) : _M_Type(pObjectType),
                                                     _M_Name(nullptr)     { 
            traits_type::construct
                (_M_Body,
                 nullptr,
                 std::forward<InitArgs>(pObjectArgs)...); 
        }

        ~basic_meta_object() { traits_type::destruct(_M_Body); }
    public:
        body_type&  body   () { return _M_Body; }
        type&       type_of() { return _M_Type; }
        const char* name   () { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        
                                      auto& operator[] (concepts::attribute auto pAttribute)       { return traits_type::get(_M_Body, pAttribute); }
        
        template <typename RhsType>   auto  operator<  (RhsType&& pRhs) { return traits_type::less_than    (*this, pRhs); }
        template <typename RhsType>   auto  operator<= (RhsType&& pRhs) { return traits_type::less_or_equal(*this, pRhs); }

        template <typename RhsType>   auto  operator>  (RhsType&& pRhs) { return traits_type::greater_than    (*this, pRhs); }
        template <typename RhsType>   auto  operator>= (RhsType&& pRhs) { return traits_type::greater_or_equal(*this, pRhs); }

        template <typename RhsType>   auto  operator== (RhsType&& pRhs) { return traits_type::equal    (*this, pRhs); }
        template <typename RhsType>   auto  operator!= (RhsType&& pRhs) { return traits_type::not_equal(*this, pRhs); }

        template <typename RhsType>   auto  operator+  (RhsType&& pRhs) { return traits_type::add          (*this, pRhs); }
        template <typename RhsType>   auto  operator+= (RhsType&& pRhs) { return traits_type::add_and_store(*this, pRhs); }

        template <typename RhsType>   auto  operator-  (RhsType&& pRhs) { return traits_type::subtract          (*this, pRhs); }
        template <typename RhsType>   auto  operator-= (RhsType&& pRhs) { return traits_type::subtract_and_store(*this, pRhs); }

        template <typename RhsType>   auto  operator*  (RhsType&& pRhs) { return traits_type::multiply          (*this, pRhs); }
        template <typename RhsType>   auto  operator*= (RhsType&& pRhs) { return traits_type::multiply_and_store(*this, pRhs); }

        template <typename RhsType>   auto  operator/  (RhsType&& pRhs) { return traits_type::divide          (*this, pRhs); }
        template <typename RhsType>   auto  operator/= (RhsType&& pRhs) { return traits_type::divide_and_store(*this, pRhs); }

        template <typename... RhsType> auto  operator=  (basic_meta_object<RhsType...>&  pRhs) { return traits_type::copy(*this, pRhs); }
        template <typename... RhsType> auto  operator=  (basic_meta_object<RhsType...>&& pRhs) { return traits_type::move(*this, pRhs); }
    };

    template <concepts::primitive MetaType, typename BodyTrait>
    class basic_meta_object<MetaType, BodyTrait> {
        using __string_view = std::string_view;
              __string_view _M_Name;
        using __body_type = typename BodyTrait::body_type;
              __body_type   _M_Body;

    public:
        basic_meta_object(const char* pName) : _M_Name(pName) {} // For CTAD Support
        basic_meta_object()                                   {}
    public:
        using body_type   = __body_type;
        using traits_type = BodyTrait;

        body_type&  body() { return _M_Body; }
        const char* name() { return (_M_Name.empty()) ? nullptr : _M_Name.data(); }
        
                                      auto& operator*  ()               { return traits_type::get(_M_Body); }
        
        template <typename RhsType>   auto  operator<  (RhsType&& pRhs) { return traits_type::less_than    (*this, pRhs); }
        template <typename RhsType>   auto  operator<= (RhsType&& pRhs) { return traits_type::less_or_equal(*this, pRhs); }

        template <typename RhsType>   auto  operator>  (RhsType&& pRhs) { return traits_type::greater_than    (*this, pRhs); }
        template <typename RhsType>   auto  operator>= (RhsType&& pRhs) { return traits_type::greater_or_equal(*this, pRhs); }

        template <typename RhsType>   auto  operator== (RhsType&& pRhs) { return traits_type::equal    (*this, pRhs); }
        template <typename RhsType>   auto  operator!= (RhsType&& pRhs) { return traits_type::not_equal(*this, pRhs); }

        template <typename RhsType>   auto  operator+  (RhsType&& pRhs) { return traits_type::add          (*this, pRhs); }
        template <typename RhsType>   auto  operator+= (RhsType&& pRhs) { return traits_type::add_and_store(*this, pRhs); }

        template <typename RhsType>   auto  operator-  (RhsType&& pRhs) { return traits_type::subtract          (*this, pRhs); }
        template <typename RhsType>   auto  operator-= (RhsType&& pRhs) { return traits_type::subtract_and_store(*this, pRhs); }

        template <typename RhsType>   auto  operator*  (RhsType&& pRhs) { return traits_type::multiply          (*this, pRhs); }
        template <typename RhsType>   auto  operator*= (RhsType&& pRhs) { return traits_type::multiply_and_store(*this, pRhs); }

        template <typename RhsType>   auto   operator/  (RhsType&& pRhs) { return traits_type::divide          (*this, pRhs); }
        template <typename RhsType>   auto   operator/= (RhsType&& pRhs) { return traits_type::divide_and_store(*this, pRhs); }

        template <typename... RhsType> auto  operator= (basic_meta_object<RhsType...>&  pRhs) { return traits_type::copy(*this, pRhs); }
        template <typename... RhsType> auto  operator= (basic_meta_object<RhsType...>&& pRhs) { return traits_type::move(*this, pRhs); }
                                       auto  operator= (MetaType pRhs)                        { return traits_type::move(*this, pRhs); }

    };
}

namespace ampersand::meta::utility {
    template <typename... AnyType>
    struct is_meta_object                                         : std::false_type {};
    template <concepts::meta_type MetaType, typename BodyTrait>
    struct is_meta_object<basic_meta_object<MetaType, BodyTrait>> : std::true_type {};
    template <typename... AnyType>
    inline constexpr bool is_meta_object_v = is_meta_object<AnyType...>::value;
}

namespace ampersand::meta::concepts {
    template <typename... AnyType>
    concept meta_object = utility::is_meta_object_v<AnyType...>;
}