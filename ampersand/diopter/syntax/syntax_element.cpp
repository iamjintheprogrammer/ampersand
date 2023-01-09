#include "syntax.hpp"
#include "syntax_element.hpp"
#include "syntax_element_constant.hpp"
#include "syntax_element_object.hpp"

namespace ampersand::diopter::syntax {
	element::element(element_category_impl pCategory)
		: impl_category(pCategory) {}

	element::~element() {
		switch (impl_category) {
			case element_category_impl::object:
				impl_category = element_category_impl::none;
				delete static_cast<object*>  (this);
				break;
			case element_category_impl::constant:
				impl_category = element_category_impl::none;
				delete static_cast<constant*>(this);
				break;
			case element_category_impl::syntax:
				impl_category = element_category_impl::none;
				delete static_cast<syntax*>  (this);
				break;
			case element_category_impl::none:
				impl_category = element_category_impl::none;
				break;
		}
	}

	element::element_category
		element::category() { return impl_category; }

	object::object
		(name_type pName, name_type pTypename)
			: impl_name(pName),
			  impl_type(pTypename),
			  element  (element_category_impl::object) {  }

	object::object
		(name_type pName, meta::primitive_category pType) 
			: impl_name			 (pName),
			  impl_type_primitive(pType),
			  element			 (element_category_impl::object) {  }

	object::name_type&		 object::name		   () { return impl_name; }
	object::name_type&		 object::type_name	   () { return impl_type; }
	meta::primitive_category object::type_primitive() { return impl_type_primitive; }

	meta::primitive_category constant::get_category() { return impl_constant_category; }
}