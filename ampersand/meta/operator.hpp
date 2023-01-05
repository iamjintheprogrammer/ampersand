#pragma once
#include <tuple>
#include <type_traits>

#include <ampersand/meta/verb.hpp>
#include <ampersand/meta/operator_impl.hpp>

namespace ampersand::meta {
	template <typename Verb, typename... Operand>
	class meta_operator {
		using __tuple = std::tuple<Operand...>;
			  __tuple _M_Base;

	public:
		using verb = Verb;
		template <std::size_t Idx, typename... T>
		friend constexpr auto& get_operand(meta_operator<T...>&);
		constexpr meta_operator(verb, Operand... pOperand) : _M_Base(pOperand...) {} // For CTAD Support
		constexpr meta_operator		 (Operand... pOperand) : _M_Base(pOperand...) {}

		AMPERSAND_DECLARE_META_OPERATOR
	};

	template <typename Verb, typename... Operand>
	meta_operator(Verb, Operand&&...)
		-> meta_operator<Verb, std::remove_reference_t<Operand>...>;

	template <std::size_t Idx, typename... T>
	constexpr auto& get_operand(meta_operator<T...>& pMeta) {
		return std::get<Idx>(pMeta._M_Base);
	}
}

namespace ampersand::meta::utility {
	template <typename... AnyType>
	struct is_meta_operator							   : std::false_type {};
	template <typename... Operand>
	struct is_meta_operator<meta_operator<Operand...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_meta_operator_v = is_meta_operator<AnyType...>::value;

	template <typename... AnyType>
	struct is_and_with						 : std::false_type {};
	template <typename... Operand>
	struct is_and_with<and_with, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_and_with_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_or_with					   : std::false_type {};
	template <typename... Operand>
	struct is_or_with<or_with, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_or_with_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_greater_than							 : std::false_type {};
	template <typename... Operand>
	struct is_greater_than<greater_than, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_greater_than_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_greater_or_equal								 : std::false_type {};
	template <typename... Operand>
	struct is_greater_or_equal<greater_or_equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_greater_or_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_less_than						   : std::false_type {};
	template <typename... Operand>
	struct is_less_than<less_than, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_less_than_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_less_or_equal							   : std::false_type {};
	template <typename... Operand>
	struct is_less_or_equal<less_or_equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_less_or_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_equal					   : std::false_type {};
	template <typename... Operand>
	struct is_equal<equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_not_equal						   : std::false_type {};
	template <typename... Operand>
	struct is_not_equal<not_equal, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_not_equal_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_add				   : std::false_type {};
	template <typename... Operand>
	struct is_add<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_add_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_add_and_store							   : std::false_type {};
	template <typename... Operand>
	struct is_add_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_add_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_subtract				   : std::false_type {};
	template <typename... Operand>
	struct is_subtract<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_subtract_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_subtract_and_store						    : std::false_type {};
	template <typename... Operand>
	struct is_subtract_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_subtract_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_multiply				   : std::false_type {};
	template <typename... Operand>
	struct is_multiply<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_multiply_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_multiply_and_store							   : std::false_type {};
	template <typename... Operand>
	struct is_multiply_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_multiply_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_divide				   : std::false_type {};
	template <typename... Operand>
	struct is_divide<add, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_divide_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_divide_and_store							   : std::false_type {};
	template <typename... Operand>
	struct is_divide_and_store<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_divide_and_store_v = is_and_with<AnyType...>::value;

	template <typename... AnyType>
	struct is_move					 : std::false_type {};
	template <typename... Operand>
	struct is_move<move, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_move_v = is_move<AnyType...>::value;

	template <typename... AnyType>
	struct is_copy					 : std::false_type {};
	template <typename... Operand>
	struct is_copy<copy, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_copy_v = is_copy<AnyType...>::value;

	template <typename... AnyType>
	struct is_not_to							: std::false_type {};
	template <typename... Operand>
	struct is_not_to<add_and_store, Operand...> : std::true_type {};
	template <typename... AnyType>
	inline constexpr bool is_not_to_v = is_not_to<AnyType...>::value;

	template <typename... AnyType>
	struct is_conditional_operator
		: std::bool_constant
			<
				is_greater_than_v	 <AnyType> ||
				is_greater_or_equal_v<AnyType> ||

				is_less_than_v	     <AnyType> ||
				is_less_or_equal_v   <AnyType> ||

				is_equal_v			 <AnyType> ||
				is_not_equal_v		 <AnyType>
			> {};

	template <typename AnyType>
	inline constexpr bool is_conditional_operator_v = is_conditional_operator<AnyType>::value;
}

namespace ampersand::meta::concepts {
	template <typename... AnyType>
	concept meta_operator = utility::is_meta_operator_v<AnyType...>;
	
	template <typename... AnyType>
	concept and_with = utility::is_and_with_v<AnyType...>;
	template <typename... AnyType>
	concept or_with  = utility::is_or_with_v<AnyType...>;
	
	template <typename... AnyType>
	concept greater_than = utility::is_greater_than_v<AnyType...>;
	template <typename... AnyType>
	concept greater_or_equal = utility::is_greater_or_equal_v<AnyType...>;

	template <typename... AnyType>
	concept less_than = utility::is_less_than_v<AnyType...>;
	template <typename... AnyType>
	concept less_or_equal = utility::is_less_or_equal_v<AnyType...>;

	template <typename... AnyType>
	concept equal	  = utility::is_equal_v<AnyType...>;
	template <typename... AnyType>
	concept not_equal = utility::is_not_equal_v<AnyType...>;

	template <typename... AnyType>
	concept add			  = utility::is_add_v<AnyType...>;
	template <typename... AnyType>
	concept add_and_store = utility::is_add_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept subtract = utility::is_subtract_v<AnyType...>;
	template <typename... AnyType>
	concept subtract_and_store = utility::is_subtract_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept multiply = utility::is_multiply_v<AnyType...>;
	template <typename... AnyType>
	concept multiply_and_store = utility::is_multiply_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept divide = utility::is_divide_v<AnyType...>;
	template <typename... AnyType>
	concept divide_and_store = utility::is_divide_and_store_v<AnyType...>;

	template <typename... AnyType>
	concept move = utility::is_move_v<AnyType...>;
	template <typename... AnyType>
	concept copy = utility::is_copy_v<AnyType...>;

	template <typename... AnyType>
	concept not_to = utility::is_not_to_v<AnyType...>;

	template <typename AnyType>
	concept conditional_operator = utility::is_conditional_operator_v<AnyType>;
}