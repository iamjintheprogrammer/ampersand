#include "type_compound.hpp"

namespace ampersand::diopter {
	compound::attribute_iterator::attribute_iterator
		(compound& pCompound, iter_impl pIter)
			: impl_compound	     (pCompound),
		      impl_value_iterator(pIter)    {  }

	type&
		compound::attribute_iterator::operator* () {
			if(impl_value_iterator == impl_compound.impl_attribute.end())
				return impl_value_error;
			else
				return *(*impl_value_iterator).second;
	}

	compound::attribute_iterator&
		compound::attribute_iterator::operator++() {
			++impl_value_iterator;
			return *this;
	}

	compound::attribute_iterator
		compound::attribute_iterator::operator++(int) {
			++impl_value_iterator;
			return *this;
	}

	bool
		compound::attribute_iterator::operator==
			(attribute_iterator& pCopy) {
		return impl_value_iterator == pCopy.impl_value_iterator;
	}

	bool
		compound::attribute_iterator::operator!=
			(attribute_iterator& pCopy) {
		return impl_value_iterator != pCopy.impl_value_iterator;
	}

	compound::nested_declare_iterator::nested_declare_iterator
		(compound& pCompound, iter_impl pIter)
			: impl_compound	     (pCompound),
		      impl_value_iterator(pIter)    {  }

	type&
		compound::nested_declare_iterator::operator* () {
			if(impl_value_iterator == impl_compound.impl_attribute.end())
				return impl_value_error;
			else
				return *(*impl_value_iterator).second;
	}

	compound::nested_declare_iterator&
		compound::nested_declare_iterator::operator++() {
			++impl_value_iterator;
			return *this;
	}

	compound::nested_declare_iterator
		compound::nested_declare_iterator::operator++(int) {
			++impl_value_iterator;
			return *this;
	}

	bool
		compound::nested_declare_iterator::operator==
			(nested_declare_iterator& pCopy) {
		return impl_value_iterator == pCopy.impl_value_iterator;
	}

	bool
		compound::nested_declare_iterator::operator!=
			(nested_declare_iterator& pCopy) {
		return impl_value_iterator != pCopy.impl_value_iterator;
	}


	compound::size_type
		compound::attribute_count() {
			return impl_attribute.size();
	}

	compound::attribute_iterator
		compound::begin_attribute() {
			return attribute_iterator(*this, impl_attribute.begin());
	}

	compound::attribute_iterator
		compound::end_attribute() {
			return attribute_iterator(*this, impl_attribute.end());
	}

	type&
		compound::find_attribute(name_type pName) {
			auto fnd_attr = impl_attribute.find(pName);
			if  (fnd_attr == impl_attribute.end())
				return impl_error;
			if (!(*fnd_attr).second)
				return impl_error;

			return *(*fnd_attr).second;
	}

	compound::size_type
		compound::nested_declare_count() {
			return impl_nested_declare.size();
	}

	compound::nested_declare_iterator
		compound::begin_nested_declare() {
			return nested_declare_iterator(*this, impl_nested_declare.begin());
	}

	compound::nested_declare_iterator
		compound::end_nested_declare() {
			return nested_declare_iterator(*this, impl_nested_declare.end());
	}

	type&
		compound::find_nested_declare(name_type) {
	}
}