#include "type_impl.hpp"

namespace ampersand::diopter {
	type_impl::type_union_impl:: type_union_impl()									  : u_table	   ()			{  }
	type_impl::type_union_impl:: type_union_impl(meta::primitive_category pPrimitive) : u_primitive(pPrimitive) {  }
	type_impl::type_union_impl::~type_union_impl()																{  }

	type_impl::type_impl
		(meta::meta_type<>& pMetaType)
			: _M_Impl_Union	   (meta::primitive_category::any),
			  _M_Impl_Primitive(true)						  {  }

	bool type_impl::link_type (name_type pName, type_ptr pImpl) {
		if (pImpl->primitive() || _M_Impl_Primitive) return false;

		auto type_linked  = _M_Impl_Union.u_table.find(pName);
		if  (type_linked == _M_Impl_Union.u_table.end()) return false;

		(*type_linked).second = pImpl;
		return true;
	}

	type_impl::type_ptr
		type_impl::operator[](name_type pName) {
			if(_M_Impl_Primitive) return type_ptr(nullptr);
			
			auto type_found = _M_Impl_Union.u_table.find(pName);
			if (type_found == _M_Impl_Union.u_table.end()) return type_ptr(nullptr);
			else										   return (*type_found).second;
	}

	type_impl::type_ptr
		type_impl::get_inner_declaration(name_type pName) {
			auto type_found = _M_Impl_Inner.find(pName);
			if (type_found == _M_Impl_Inner.end()) return type_ptr(nullptr);
			else								   return (*type_found).second;
	}

	type_impl::type_ptr
		type_impl::super_declaration() {
			return _M_Impl_Super;
	}

	bool
		type_impl::primitive()
			{ return _M_Impl_Primitive; }

	bool
		type_impl::inner_declaration()
			{ return _M_Impl_Super != nullptr; }

	type_impl::name_type
		type_impl::name() { return _M_Impl_TypeName; }
}