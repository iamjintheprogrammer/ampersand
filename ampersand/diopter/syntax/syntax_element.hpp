#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter::syntax {
	class element {
		friend class syntax  ;
		friend class constant;
		friend class object  ;

		enum class element_category_impl { object, constant, syntax, none };
		element_category_impl impl_category;
		element(element_category_impl);
	public:
		using element_category = element_category_impl;
		~element();
		
		element_category category();
	};
}