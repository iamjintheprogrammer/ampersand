#pragma once
#include <ampersand/diopter/component.hpp>

namespace ampersand::diopter {
	template <concepts::component... Component>
	class scope {
		using __tuple = std::tuple<Component...>;
			  __tuple _M_Component;
	public:
		scope(Component... pComponent) : _M_Component(pComponent...) {}
		template <std::size_t Idx, concepts::component... Component>
		friend auto& get_component(scope<Component...>&);
	};

	template <concepts::component... Component>
	scope(Component...) -> scope <Component...>;

	template <std::size_t Idx, concepts::component... Component>
	auto
		get_component
			(scope<Component...>& pScope) {
		return
			std::get<Idx>(pScope._M_Component);
	}
}

namespace ampersand::diopter::utility {
	template <typename... AnyType>
	struct is_scope					   : std::false_type {};
	template <typename... AnyType>
	struct is_scope<scope<AnyType...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_scope_v = is_scope<AnyType...>::value;
}

namespace ampersand::diopter::concepts {
	template <typename... AnyType>
	concept scope = utility::is_scope_v<AnyType...>;
}