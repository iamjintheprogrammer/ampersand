#pragma once
#include <tuple>

#include <ampersand/meta/method.hpp>
#include <ampersand/meta/attribute.hpp>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::meta {
    template <typename... AnyType>
    class implementation;

    template <typename ObjectT, concepts::method... Methods>
    class implementation<ObjectT, trait<Methods...>>
    {
        using __trait     = std::tuple<Methods...>;
    public:
        using object_type = ObjectT;
        using traits_type = trait<Methods...>;

    public:
        implementation(object_type& pObject)
            : _M_Object(pObject) {}

    public:
        template <typename Attr>
        auto& operator[](Attr) { _M_Object[Attr{}]; }
        template <typename Method, typename... Args>
        auto operator()(Method, Args&&... pArgs) {
            return
                std::tuple_element_t
                    <boost::mp11::mp_find<typename traits_type::type, Method>::value, __trait>::value
                        (_M_Object, std::forward<Args>(pArgs)...);
        }

    private:
        __trait       _M_Trait ;
        object_type&  _M_Object;
    };
}