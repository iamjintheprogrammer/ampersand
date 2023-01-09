#include "type_function_argument.hpp"

namespace ampersand::diopter {
	function::argument::argument(function& pFunction)
		: impl_function(pFunction) { }

	function::argument::iterator::iterator
		(function& pFunction, function::args_impl::iterator pIterator)
			: impl_function(pFunction),
			  impl_iterator(pIterator) {}
	
	type&
		function::argument::iterator::operator* () {
			if(impl_iterator == impl_function.impl_argument.end())
				return impl_function.impl_argument_error;
			else
				return *(*impl_iterator).second;
	}

	type::name_type&
		function::argument::iterator::name() {
			return (*impl_iterator).first;
	}

	function::argument::iterator&
		function::argument::iterator::operator++() {
			++impl_iterator;
			return *this;
	}

	function::argument::iterator
		function::argument::iterator::operator++(int) {
			++impl_iterator;
			return *this;
	}

	bool
		function::argument::iterator::operator==
			(iterator& pIterator) {
		return impl_iterator == pIterator.impl_iterator;
	}

	bool
		function::argument::iterator::operator!=
			(iterator& pIterator) {
		return impl_iterator != pIterator.impl_iterator;
	}

	function::argument::iterator
		function::argument::begin() {
			return iterator(impl_function, impl_function.impl_argument.begin());
	}

	function::argument::iterator
		function::argument::end() {
			return iterator(impl_function, impl_function.impl_argument.end());
	}

	function::argument::iterator
		function::argument::find(key_type pKey) {
			return iterator(impl_function, impl_function.impl_argument.find(pKey));
	}

	function::argument::reference
		function::argument::operator[](key_type pKey) {
			auto it_found = impl_function.impl_argument.find(pKey);
			return
				(it_found == impl_function.impl_argument.end())
					? impl_function.impl_argument_error
					: *(*it_found).second;
	}
}