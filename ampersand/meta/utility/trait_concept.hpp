#pragma once
#include <ampersand/meta/utility/trait.hpp>

namespace ampersand::meta::concepts {
    template <typename AttrT>   concept attribute   = utility::template is_attribute_v  <AttrT>;
    template <typename AnnotT>  concept annotation  = utility::template is_annotation_v <AnnotT>;
    template <typename ObjectT> concept meta_object = utility::template is_meta_object_v<ObjectT>;
    template <typename ObjectT> concept meta_type   = utility::template is_meta_type_v  <ObjectT>;
}

namespace ampersand::meta::utility {
    template
        <meta::concepts::attribute AttrT,
            template <typename...> typename Predicate>
    struct has_annotation {
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <boost::mp11::mp_list<typename AttrT::annotations>, Predicate>::value
                        != boost::mp11::mp_size<typename AttrT::annotations>::value);
    };

    template
        <meta::concepts::meta_object ObjectT,
            meta::concepts::attribute Attribute>
    struct has_attribute {
    private:
        template <typename AnyType>
        using has_attribute_impl = std::is_same<AnyType, Attribute>;
    public:
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <typename ObjectT::meta_type::type, has_attribute_impl>::value
                        != boost::mp11::mp_size<typename ObjectT::meta_type::type>::value);
    };

    template
        <meta::concepts::meta_object ObjectT,
            template <typename...> typename Predicate>
    struct has_annotated_attribute {
    private:
        template <typename AttrT>
        using has_annotated_attribute_impl = has_annotation<AttrT, Predicate>;
    public:
        static constexpr bool value
            = (boost::mp11::mp_find_if
                    <typename ObjectT::meta_type::type, has_annotated_attribute_impl>::value
                        != boost::mp11::mp_size<typename ObjectT::meta_type::type>::value);
    };    
}