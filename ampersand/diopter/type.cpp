#include "type.hpp"

#include "type_compound.hpp"
#include "type_primitive.hpp"
#include "type_function.hpp"

namespace ampersand::diopter {
	type::type(name_impl pName, category_impl pCategory)
		: impl_type_name	(pName)	  ,
		  impl_type_category(pCategory) {}

	type::type(category_impl pCategory)
		: impl_type_name    (),
		  impl_type_category(pCategory) {}

	type::~type() {
		switch (impl_type_category) {
			case category_impl::compound :
				impl_type_category = category_impl::none;
				delete static_cast<compound*> (this);
				break;
			case category_impl::primitive:
				impl_type_category = category_impl::none;
				delete static_cast<primitive*>(this);
				break;
			case category_impl::none:
				break;
		}
	}

	type::name_type type::type_name	   () { return impl_type_name	 ; }
	type::category  type::type_category() { return impl_type_category; }
}