#include "type_compound_nested.hpp"

namespace ampersand::diopter {
	compound::nested_declare::nested_declare(compound& pCompound)
		: impl_compound(pCompound) { }

	compound::nested_declare::iterator::iterator
		(compound& pCompound, compound::table_impl::iterator pIterator)
			: impl_compound(pCompound),
			  impl_iterator(pIterator) {}
	
	type&
		compound::nested_declare::iterator::operator* () {
			if(impl_iterator == impl_compound.impl_nested_declare.end())
				return impl_compound.impl_error;
			else
				return *(*impl_iterator).second;
	}

	compound::nested_declare::iterator&
		compound::nested_declare::iterator::operator++() {
			++impl_iterator;
			return *this;
	}

	compound::nested_declare::iterator
		compound::nested_declare::iterator::operator++(int) {
			++impl_iterator;
			return *this;
	}

	bool
		compound::nested_declare::iterator::operator==
			(iterator& pIterator) {
		return impl_iterator == pIterator.impl_iterator;
	}

	bool
		compound::nested_declare::iterator::operator!=
			(iterator& pIterator) {
		return impl_iterator != pIterator.impl_iterator;
	}

	compound::nested_declare::iterator
		compound::nested_declare::begin() {
			return iterator(impl_compound, impl_compound.impl_nested_declare.begin());
	}

	compound::nested_declare::iterator
		compound::nested_declare::end() {
			return iterator(impl_compound, impl_compound.impl_nested_declare.end());
	}

	compound::nested_declare::iterator
		compound::nested_declare::find(key_type pKey) {
			return iterator(impl_compound, impl_compound.impl_nested_declare.find(pKey));
	}

	compound::nested_declare::reference
		compound::nested_declare::operator[](key_type pKey) {
			auto it_found = impl_compound.impl_nested_declare.find(pKey);
			return
				(it_found == impl_compound.impl_nested_declare.end())
					? impl_compound.impl_error
					: *(*it_found).second;
	}
}