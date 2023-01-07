#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/operator.hpp>

namespace ampersand::meta::utility {
	template <typename T>
	struct is_meta_script_element
		: std::disjunction
			<
				is_meta_object  <T>,
				is_meta_type    <T>,
				is_meta_operator<T>
			> {};

	template <typename T>
	inline constexpr bool is_meta_script_element_v = is_meta_script_element<T>::value;
}

namespace ampersand::meta::concepts {
	template <typename T>
	concept meta_script_element = utility::is_meta_script_element_v<T>;
}

namespace ampersand::meta {
	template <concepts::meta_script_element... Element>
	class meta_script {
		using tuple_impl = std::tuple<Element...>;
		tuple_impl _M_Impl_Element;
	public:
		constexpr meta_script(Element... pElement)
			: _M_Impl_Element(pElement...) {}
		template 
			<std::size_t Idx,
				concepts::meta_script_element... InputElement>
		friend constexpr auto&	    get_script_element	     (meta_script<InputElement...>&);
		template 
			<concepts::meta_script_element... InputElement>
		friend constexpr std::size_t get_script_element_count(meta_script<InputElement...>&);
	};

	template <concepts::meta_script_element... Element>
	meta_script(Element...) -> meta_script<Element...>;

	template
		<std::size_t Idx,
			concepts::meta_script_element... InputElement>
	constexpr auto&
		get_script_element
			(meta_script<InputElement...>& pElement) {
		return
			std::get<Idx>(pElement._M_Impl_Element);
	}

	template
		<concepts::meta_script_element... InputElement>
	constexpr std::size_t
		get_script_element_count
			(meta_script<InputElement...>& pElement) {
		return
			sizeof...(InputElement);
	}
}

namespace ampersand::meta::utility {
	template <typename T>
	struct is_meta_script					 : std::false_type {};
	template <typename... T>
	struct is_meta_script<meta_script<T...>> : std::true_type  {};

	template <typename T>
	inline constexpr bool is_meta_script_v = is_meta_script_element<T>::value;
}

namespace ampersand::meta::concepts {
	template <typename T>
	concept meta_script = utility::is_meta_script_v<T>;
}