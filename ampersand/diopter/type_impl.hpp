#pragma once
#include <memory>
#include <unordered_map>

#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	class type_impl {
		using __table = std::unordered_map<std::string, std::shared_ptr<type_impl>>;
		union type_union_impl {
			  __table				   u_table    ; // Enabled If this type is Compound Type.
			  meta::primitive_category u_primitive; // Enabled If this type is Primitive Type.

			   type_union_impl();
			   type_union_impl(meta::primitive_category);
			  ~type_union_impl();
		}			_M_Impl_Union      ;
		bool		_M_Impl_Primitive  ;
		std::string _M_Impl_TypeName   ;

		__table					   _M_Impl_Inner;
		std::shared_ptr<type_impl> _M_Impl_Super;

		template <std::size_t Idx,    typename... T> void _M_Impl_Init(meta::meta_type<T...>&);
		template <std::size_t... Idx, typename... T> void _M_Impl_Init(meta::meta_type<T...>&, std::index_sequence<Idx...>);
	public:
		using name_type = std::string;
		using type_ptr  = std::shared_ptr<type_impl>;

		template <typename... T> type_impl(meta::meta_type<T...>&)        ;
								 type_impl(meta::meta_type<>&)			  ;
								 type_impl(meta::concepts::primitive auto);
								~type_impl() {}

	public:
		name_type name		();
		bool	  link_type (name_type, type_ptr);
		
		bool	  primitive		   ();
		bool	  inner_declaration(); // Returns True if the type is Inner Declaration (Nested Class)
		
		type_ptr  operator[]		   (name_type);
		type_ptr  get_inner_declaration(name_type);
		type_ptr	  super_declaration();
	};

	template <std::size_t Idx, typename... T>
	void 
		type_impl::_M_Impl_Init
			(meta::meta_type<T...>& pMetaType) {
		auto  attr      = meta::get_attribute<Idx>(pMetaType);
		using attr_type = std::remove_reference_t<decltype(attr)>;

		if constexpr
			(meta::utility::is_primitive_attribute_v<attr_type>)
				_M_Impl_Union.u_table.insert
					(std::make_pair(attr.name(), std::make_shared<type_impl>(attr.type())));
		else
			_M_Impl_Union.u_table.insert
				(std::make_pair(attr.name(), type_ptr(nullptr)));
	}
	template <std::size_t... Idx, typename... T>
	void
		type_impl::_M_Impl_Init
			(meta::meta_type<T...>& pMetaType, std::index_sequence<Idx...>) {
		( _M_Impl_Init<Idx>(pMetaType), ...);
	}

	template <typename... T>
	type_impl::type_impl
		(meta::meta_type<T...>& pMetaType)
			: _M_Impl_Union    (),
			  _M_Impl_Primitive(false),
			  _M_Impl_TypeName (pMetaType.type_id()) {
			  _M_Impl_Init	   (pMetaType, std::make_index_sequence<sizeof...(T)>{});
	}

	type_impl::type_impl
		(meta::concepts::primitive auto pPrimitive)
			: _M_Impl_Union	   (pPrimitive.type_id()),
			  _M_Impl_Primitive(true)				 {  }
}