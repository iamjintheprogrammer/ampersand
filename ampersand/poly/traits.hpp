#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/body/tag.hpp>
#include <string>

namespace ampersand::poly {
	template <typename Fn>
	class functional {
		using __fn = Fn;
			  __fn* _M_Func;
	public:
		functional(Fn);
		functional()  {}

		template <typename... Args>
		auto operator()(Args&&...);
	};

	template <typename Fn>
	functional<Fn>::functional(Fn pFunc)
		: _M_Func(pFunc) {}

	template <typename Fn>
	template <typename... Args>
	auto
		functional<Fn>::operator()(Args&&... pArgs) {
			return
				std::apply(_M_Func, pArgs...);
	}

	template <typename Fn>
	functional(Fn) -> functional<Fn>;

	template <typename... FunctionalAttr>
	class traits 
		: public meta::meta_object
				<meta::body::tag<std::string>,
				 meta::meta_type<FunctionalAttr...>> {
	public:
		template <typename... InFunctional>
		traits()
	};
}