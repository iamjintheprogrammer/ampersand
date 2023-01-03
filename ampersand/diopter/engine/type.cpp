#include "type.hpp"

namespace ampersand::diopter {
	type::primitive::primitive
		(primitive_type_impl& pInit) : _M_Impl(&pInit) { }

	type::primitive::primitive_category
		type::primitive::category() {
			return _M_Impl->category;
	}

	type::complex::complex
		(complex_type_impl& pInit) : _M_Impl(&pInit) {  }

	void
		type::complex::push_subtype
			(string_type pName, type& pType) {
		_M_Impl->table.insert
			(std::make_pair(pName, new type_impl(pType._M_Impl)));
	}
}