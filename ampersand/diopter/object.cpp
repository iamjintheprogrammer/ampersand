#include "object.hpp"

namespace ampersand::diopter {
	dynamic_object_impl::dynamic_object_impl(name_type pName, type& pType)
		: _M_Type(pType),
		  _M_Name(pName) {}

	dynamic_object_impl::~dynamic_object_impl() { }

	type						   dynamic_object_impl::type_of() { return _M_Type; }
	dynamic_object_impl::name_type dynamic_object_impl::name   () { return _M_Name; }

	constant_object_impl::constant_object_impl(name_type pName, type& pType)
		: _M_Type(pType),
		  _M_Name(pName) {}

	constant_object_impl::~constant_object_impl() { }

	type						    constant_object_impl::type_of() { return _M_Type; }
	constant_object_impl::name_type constant_object_impl::name   () { return _M_Name; }

	object::object
		(category pCategory, name_type pName, type& pType)
			: _M_Impl_Category(pCategory) {
		switch (pCategory) {
			case category::constant:
				_M_Impl_Constant = constant_object_impl(pName, pType);
				break;
			case category::dynamic:
				_M_Impl_Dynamic  = dynamic_object_impl (pName, pType);
				break;
		}
	}

	object::object()
		: _M_Impl_Category(category::none) {} 

	object::object(const object& pCopy) 
		: _M_Impl_Category(pCopy._M_Impl_Category) {
		switch (_M_Impl_Category) {
			case category::constant:
				_M_Impl_Constant = pCopy._M_Impl_Constant;
				break;
			case category::dynamic:
				_M_Impl_Dynamic = pCopy._M_Impl_Dynamic;
				break;
		}
	}

	object::object(object&& pMove) 
		: _M_Impl_Category(pMove._M_Impl_Category) {
		switch (_M_Impl_Category) {
			case category::constant:
				_M_Impl_Constant = std::move(pMove._M_Impl_Constant);
				break;
			case category::dynamic:
				_M_Impl_Dynamic  = std::move(pMove._M_Impl_Dynamic);
				break;
		}
	}

	type object::type_of() {
		switch (_M_Impl_Category) {
			case category_impl::dynamic:
				return _M_Impl_Dynamic.type_of();
			case category_impl::constant:
				return _M_Impl_Constant.type_of();
			case category_impl::none:
				return type{};
		}
	}

	object::name_type object::name() {
		switch (_M_Impl_Category) {
			case category_impl::dynamic:
				return _M_Impl_Dynamic .name();
			case category_impl::constant:
				return _M_Impl_Constant.name();
			case category_impl::none:
				return name_type {};
		}
	}

	object::category object::get_category() {
		return _M_Impl_Category;
	}

	object::operator bool() {
		return _M_Impl_Category != category_impl::none;
	}
}