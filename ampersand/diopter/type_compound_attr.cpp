#include "type_compound_attr.hpp"

namespace ampersand::diopter {
	compound::attribute::attribute(compound& pCompound)
		: impl_compound(pCompound) { }

	compound::attribute::iterator::iterator
		(compound& pCompound, compound::table_impl::iterator pIterator)
			: impl_compound(pCompound),
			  impl_iterator(pIterator) {}
	
	type::name_type
		compound::attribute::iterator::name() {
			return (*impl_iterator).first;
	}

	type&
		compound::attribute::iterator::operator* () {
			if(impl_iterator == impl_compound.impl_attribute.end())
				return impl_compound.impl_error;
			if (!(*impl_iterator).second)
				return impl_compound.impl_error;
				return *(*impl_iterator).second;
	}

	compound::attribute::iterator&
		compound::attribute::iterator::operator++() {
			++impl_iterator;
			return *this;
	}

	compound::attribute::iterator
		compound::attribute::iterator::operator++(int) {
			++impl_iterator;
			return *this;
	}

	bool
		compound::attribute::iterator::operator==
			(iterator& pIterator) {
		return impl_iterator == pIterator.impl_iterator;
	}

	bool
		compound::attribute::iterator::operator!=
			(iterator& pIterator) {
		return impl_iterator != pIterator.impl_iterator;
	}

	compound::attribute::iterator
		compound::attribute::begin() {
			return iterator(impl_compound, impl_compound.impl_attribute.begin());
	}

	compound::attribute::iterator
		compound::attribute::end() {
			return iterator(impl_compound, impl_compound.impl_attribute.end());
	}

	compound::attribute::iterator
		compound::attribute::find(key_type pKey) {
			return iterator(impl_compound, impl_compound.impl_attribute.find(pKey));
	}

	compound::attribute::reference
		compound::attribute::operator[](key_type pKey) {
			auto it_found = impl_compound.impl_attribute.find(pKey);
			return
				(it_found == impl_compound.impl_attribute.end())
					? impl_compound.impl_error
					: *(*it_found).second;
	}
}