#pragma once
#include <ampersand/diopter/function.hpp>

namespace ampersand::diopter {
	class impl {
		std::vector<function> _M_Impl_Func ;
		type				  _M_Impl_Type ;
		scope				  _M_Impl_Scope;
	public:
		impl(scope, type&, meta::concepts::meta_method auto...);
		impl(scope, type&);

	public:
		type&    get_impl_type    ();
		scope&   get_impl_scope   ();
		function get_impl_function(std::size_t);
	};

	impl::impl
		(scope pScope, type& pType,
			meta::concepts::meta_method auto... pMethods)
				: _M_Impl_Type (pType),
				  _M_Impl_Scope(pScope) {
		((_M_Impl_Func.emplace_back(_M_Impl_Scope, pMethods)), ...);
	}
}