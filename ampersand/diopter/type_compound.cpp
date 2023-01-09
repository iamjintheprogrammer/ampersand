#include "type_compound.hpp"

namespace ampersand::diopter {
	type&
		compound::get_super() {
			return
				(impl_nested_super)
					? *impl_nested_super
					:  impl_error;
	}

	std::shared_ptr<type>
		compound::impl_find_type
			(compound& pCompound, name_type pTypename) {
		auto sym_found = pCompound.impl_nested_declare.find(pTypename);
		return
			(sym_found == pCompound.impl_nested_declare.end())
				? std::shared_ptr<type> { nullptr }
				: (*sym_found).second;
	}

	std::shared_ptr<type>
		compound::impl_find_type_from_super
			(compound& pCompound, name_type pTypename) {
		compound* type_seek = pCompound.impl_nested_super;
		while(type_seek) {
			auto sym_found = type_seek->impl_nested_declare.find(pTypename);
			if (sym_found == type_seek->impl_nested_declare.end()) {
				type_seek  = type_seek->impl_nested_super;
				continue;
			}

			return (*sym_found).second;
		}

		return std::shared_ptr<type> { nullptr };
	}

	std::shared_ptr<type>
		compound::impl_find_type_from_nested
			(compound& pCompound, name_type pTypename) {
		for(auto it_nested  = pCompound.impl_nested_declare.begin();
				 it_nested != pCompound.impl_nested_declare.end  ();
			   ++it_nested) {
			std::shared_ptr<type>& type_nested     = (*it_nested).second;
			compound*			   type_nested_ptr = static_cast<compound*>(type_nested.get());
			
			if (type_nested_ptr->impl_nested_declare.empty()) {
				if (type_nested_ptr->type_name() == pTypename)
					return type_nested;
			}
			else {
				auto type_ptr = impl_find_type_from_nested(*type_nested_ptr, pTypename);
				if (type_ptr) return type_ptr;
			}
		}

		return std::shared_ptr<type> { nullptr };
	}

	std::shared_ptr<type>
		compound::impl_find_type_from_all
			(compound& pCompound, name_type pTypename) {
		std::shared_ptr<type> type_found;
		
		   type_found = compound::impl_find_type(pCompound, pTypename);
		if(type_found) return type_found;

			type_found = compound::impl_find_type_from_nested(pCompound, pTypename);
		if (type_found) return type_found;

			type_found = compound::impl_find_type_from_super(pCompound, pTypename);
		if (type_found) return type_found;

		return std::shared_ptr<type> { nullptr };
	}

	type&
		compound::find_type
			(compound& pCompound, name_type pTypename) {
		auto ptr_type = compound::impl_find_type(pCompound, pTypename);

		return
			(ptr_type) ? *ptr_type : pCompound.impl_error;
	}

	type&
		compound::find_type_from_super
			(compound& pCompound, name_type pTypename) {
		auto ptr_type = compound::impl_find_type_from_super(pCompound, pTypename);

		return
			(ptr_type) ? *ptr_type : pCompound.impl_error;
	}

	type&
		compound::find_type_from_nested
			(compound& pCompound, name_type pTypename) {
		auto ptr_type = compound::impl_find_type_from_nested(pCompound, pTypename);
		
		return
			(ptr_type) ? *ptr_type : pCompound.impl_error;
	}

	type&
		compound::find_type_from_all
			(compound& pCompound, name_type pTypename) {
		auto ptr_type = compound::impl_find_type_from_all(pCompound, pTypename);

		return
			(ptr_type) ? *ptr_type : pCompound.impl_error;
	}
}