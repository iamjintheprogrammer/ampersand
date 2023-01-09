#include "syntax.hpp"

namespace ampersand::diopter::syntax {
	element& 
		syntax::operator[](size_type pIndex) {
			if(pIndex >= impl_element.size())
				return  impl_element_error;
			else
				return *impl_element[pIndex];
	}
}