#include "object_impl.hpp"

namespace ampersand::diopter {
	primitive_object_impl::primitive_object_impl
		(type::primitive& pPrimitive) { }

	complex_object_impl::complex_object_impl
		(type::complex& pComplex) {
			type::complex::subtype it_subtype(pComplex);
			for( ; it_subtype ; ++it_subtype) {
				type t_subtype = it_subtype.get_type();
				table.insert
					(std::make_pair
						(it_subtype.name(), new object_impl(t_subtype)));
			}
	}

	object_impl::u_object_impl::u_object_impl()
		: u_none() {}

	object_impl::u_object_impl::~u_object_impl() {}

	object_impl::object_impl(type& pType, type::string_type pName)
		: name	     (pName),
		  object_type(pType),
		  u_object   ()     {
			switch (object_type.type_category()) {
				case type::category::complex: {
					type::complex					 t_complex;
					object_type.get_implemented_type(t_complex);

					u_object.u_complex = complex_object_impl(t_complex);
					break;
				}
				case type::category::primitive: {
					type::primitive					 t_primitive;
					object_type.get_implemented_type(t_primitive);

					u_object.u_primitive = primitive_object_impl(t_primitive);
					break;
				}
			}
	}

	object_impl::object_impl(type& pType)
		: name	     ()	    ,
		  object_type(pType),
		  u_object   ()     {
			switch (object_type.type_category()) {
				case type::category::complex: {
					type::complex					 t_complex;
					object_type.get_implemented_type(t_complex);

					u_object.u_complex = complex_object_impl(t_complex);
					break;
				}
				case type::category::primitive: {
					type::primitive					 t_primitive;
					object_type.get_implemented_type(t_primitive);

					u_object.u_primitive = primitive_object_impl(t_primitive);
					break;
				}
			}
	}
}