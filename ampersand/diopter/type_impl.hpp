#pragma once
#include <memory>
#include <unordered_map>

#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	class type_impl {
		using __table = std::unordered_map<std::string, std::shared_ptr<type_impl>>;
		__table				       _M_Impl_Complex		   ; // Enabled If this type is Compound Type.
		std::string				   _M_Impl_Complex_TypeName; // Type name of Complex Type.
		__table					   _M_Impl_Complex_Inner   ; // Inner Type Declaration of Complex Type.
		std::shared_ptr<type_impl> _M_Impl_Complex_Super   ; // Super Type Declaration of Complex Type.
		
		meta::primitive_category _M_Impl_Primitive_Category; // Enabled If this type is Primitive Type.
		bool					 _M_Impl_Primitive;

		
													 void _M_Impl_Init(meta::concepts::attribute		   auto&);
													 void _M_Impl_Init(meta::concepts::primitive_attribute auto&);
													 void _M_Impl_Init(meta::concepts::meta_type		   auto&);
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

	void
		type_impl::_M_Impl_Init
			(meta::concepts::attribute auto& pAttr) {
		_M_Impl_Complex.insert
			(std::make_pair(pAttr.name(), type_ptr(nullptr)));
	}

	void
		type_impl::_M_Impl_Init
			(meta::concepts::primitive_attribute auto& pAttr) {
		_M_Impl_Complex.insert
			(std::make_pair(pAttr.name(), std::make_shared<type_impl>(pAttr.type())));
	}
	void 
		type_impl::_M_Impl_Init
			(meta::concepts::meta_type auto& pType) {
		_M_Impl_Complex_Inner.insert
			(pType.type_id(), std::make_shared<type_impl>(pType));
	}

	template <std::size_t Idx, typename... T>
	void 
		type_impl::_M_Impl_Init
			(meta::meta_type<T...>& pMetaType) {
		auto  attr = meta::get_attribute<Idx>(pMetaType);
		_M_Impl_Init(attr);
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