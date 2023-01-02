#pragma once
#include <ampersand/diopter/component_traits.hpp>

namespace ampersand::diopter {
	template <concepts::component_element... Element>
	class component {
		using __tuple = std::tuple<Element...>;
			  __tuple _M_Component;
	public:
		constexpr component(Element... pComponent) : _M_Component(pComponent...) {}
		template <std::size_t Idx, concepts::component_element... RhsElement>
		friend auto get_element(component<RhsElement...>&);
	};

	template <concepts::component_element... Element>
	component(Element...) -> component<Element...>;

	template <std::size_t Idx, concepts::component_element... Element>
	auto
		get_element
			(component<Element...>& pComponent) {
		return
			std::get<Idx>(pComponent);
	}
}

namespace ampersand::diopter::utility {
	template <typename... AnyType>
	struct is_component						   : std::false_type {};
	template <typename... AnyType>
	struct is_component<component<AnyType...>> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_component_v = is_component<AnyType...>::value;
}

namespace ampersand::diopter::concepts {
	template <typename... AnyType>
	concept component = utility::is_component_v<AnyType...>;
}