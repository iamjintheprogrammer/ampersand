#include "type_impl.hpp"

namespace ampersand::diopter {
	void 
		complex_type_impl::push_subtype_impl
			(std::string pName, std::string pTypeName, complex_type_impl& pComplex) {
		table.insert
			(std::make_pair
				(pName, new type_impl(pTypeName, pComplex)));
	}

	void 
		complex_type_impl::push_subtype_impl
			(std::string pName, primitive_type_impl& pPrimitive) {
		table.insert
			(std::make_pair
				(pName, new type_impl(pPrimitive)));
	}

	void
		complex_type_impl::pop_subtype_impl
			(std::string pName) {
		table.erase(pName);
	}

	type_impl::u_type_impl::u_type_impl() 
		: u_primitive
			(primitive_type_impl::primitive_category::any)
				{  }

	type_impl::u_type_impl::u_type_impl (complex_type_impl&   pInit) : u_complex  (pInit) {}
	type_impl::u_type_impl::u_type_impl (primitive_type_impl& pInit) : u_primitive(pInit) {}
	type_impl::u_type_impl::~u_type_impl()												  {}

	type_impl::type_impl
		(complex_type_impl& pComplex)
			: u_type(pComplex)			 {  }
	
	type_impl::type_impl(primitive_type_impl& pPrimitive)
		: u_type(pPrimitive) {}

	type_impl::type_impl() : u_type() {}
	
	type_impl::type_impl(const type_impl& pCopy)
		: category(pCopy.category),
		  u_type  ((pCopy.category == type_category::complex)
						? pCopy.u_type.u_complex
						: pCopy.u_type.u_primitive)  {  }

	primitive_type_impl::primitive_type_impl
		(primitive_category pCategory) : category(pCategory) {  }
}