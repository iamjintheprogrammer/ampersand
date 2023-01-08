#include "type.hpp"

namespace ampersand::diopter {
	type::type(name_impl pName, category_impl pCategory)
		: impl_type_name	(pName)	  ,
		  impl_type_category(pCategory) {}

	type::type(category_impl pCategory)
		: impl_type_name    (),
		  impl_type_category(pCategory) {}

	type::name_type type::type_name	   () { return impl_type_name	 ; }
	type::category  type::type_category() { return impl_type_category; }
}