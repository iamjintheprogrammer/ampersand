#include "type.hpp"

namespace ampersand::diopter {
	type::type(type_impl::type_ptr pImpl) : _M_Impl(pImpl)								{  }
	type::type(meta::meta_type<>& pType)  : _M_Impl(std::make_shared<type_impl>(pType)) {  }
	type::type()						  : _M_Impl(type_impl::type_ptr(nullptr))		{  }

	type::name_type 
		type::name() { 
			if(!_M_Impl)
				return name_type();
				return _M_Impl->name(); 
	}
	
	bool
		type::link_type
			(name_type pName, type& pType) {
		if (!_M_Impl)
			return false;
		return
			_M_Impl->link_type
				(pName, pType._M_Impl);
	}

	bool
		type::primitive() {
			if (!_M_Impl)
				return false;
				return _M_Impl->primitive();
	}

	type
		type::operator[](name_type pName) {
			if(!_M_Impl)
				return type();
				return type(_M_Impl->operator[](pName));
	}

	bool
		type::inner_declaration() {
			return _M_Impl->inner_declaration();
	}

	type
		type::super_declaration(name_type pName) {
			return type(_M_Impl->super_declaration());
	}

	type
		type::get_inner_declaration(name_type pName) {
			if(!_M_Impl)
				return type();
				return type(_M_Impl->get_inner_declaration(pName));
	}

	type::operator bool() {
		return _M_Impl.operator bool();
	}
}