#include "type_primitive.hpp"

namespace ampersand::diopter {
	primitive::~primitive() {}
	meta::primitive_category
		primitive::primitive_category() {
			return impl_category;
	}
}