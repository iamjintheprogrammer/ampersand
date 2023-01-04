#include "type.hpp"

namespace ampersand::diopter {
	type::type(type_impl::type_ptr pImpl) : _M_Impl(pImpl)								{  }
	type::type(meta::meta_type<>& pType)  : _M_Impl(std::make_shared<type_impl>(pType)) {  }

	type::name_type 
		type::name() { return _M_Impl->name(); }
	
	bool
		type::link_type
			(name_type pName, type& pType) {
		return
			_M_Impl->link_type
				(pName, pType._M_Impl);
	}

	bool
		type::primitive() {
			return _M_Impl->primitive();
	}

	type
		type::operator[](name_type pName) {
			return
				type(_M_Impl->operator[](pName));
	}
}