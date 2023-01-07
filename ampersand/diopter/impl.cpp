#include "impl.hpp"

namespace ampersand::diopter {
	impl::impl(scope pScope, type& pType)
		: _M_Impl_Type (pType),
		  _M_Impl_Scope(pScope) {}

	type&    impl::get_impl_type	()					 { return _M_Impl_Type ; }
	scope&   impl::get_impl_scope	()					 { return _M_Impl_Scope; }
	function impl::get_impl_function(std::size_t pIndex) { 
		if (pIndex >= _M_Impl_Func.size())
			return function{};
		else
			return _M_Impl_Func[pIndex];
	}
}