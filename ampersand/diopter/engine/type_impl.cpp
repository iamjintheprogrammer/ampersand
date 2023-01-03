#include "type_impl.hpp"

namespace ampersand::diopter {
	complex_type_impl::complex_type_impl
		(std::string pName) : name(pName) { }

	complex_type_impl::~complex_type_impl() {
		for (auto it_destruct : table)
			delete it_destruct.second;
	}

	void 
		complex_type_impl::push_subtype_impl
			(std::string pName, complex_type_impl& pComplex) {
		table.insert
			(std::make_pair
				(pName, new type_impl(pComplex)));
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

	type_impl::u_type_impl::u_type_impl()							   : u_none		()			{}
	type_impl::u_type_impl::u_type_impl(std::string pName)			   : u_complex  (pName)	    {}
	type_impl::u_type_impl::u_type_impl(primitive_type_impl pCategory) : u_primitive(pCategory) {}
	type_impl::u_type_impl::u_type_impl(complex_type_impl& pComplex)   : u_complex  (pComplex)  {}
	type_impl::u_type_impl::~u_type_impl() {}

	type_impl::type_impl(complex_type_impl& pComplex)    : u_type(pComplex)   {  }
	type_impl::type_impl(primitive_type_impl pPrimitive) : u_type(pPrimitive) {  }
	type_impl::type_impl()								 : u_type()		   {  }
	type_impl::type_impl(std::string pName)				 : u_type(pName),
														   category(type_category::complex) {}
	type_impl::type_impl(primitive_type_impl pCategory)
		: u_type  (pCategory)				,
		  category(type_category::primitive) {}

	type_impl::type_impl(const type_impl& pCopy)
		: u_type() {
			category = pCopy.category;
			if	   (category == type_category::complex)
				u_type.u_complex   = pCopy.u_type.u_complex;
			else if(category == type_category::primitive)
				u_type.u_primitive = pCopy.u_type.u_primitive;
	}

}