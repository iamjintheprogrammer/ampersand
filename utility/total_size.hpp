#pragma once
#include <type_traits>

namespace ampersand::utility {
	template <typename... T>
	struct __total_size;

	template <typename T, typename... Types>
	struct __total_size<T, Types...> {
		static constexpr std::size_t
			value = sizeof(T)
				  + __total_size<Types...>::value;
	};

	template <typename T>
	struct __total_size<T> {
		static constexpr std::size_t
			value = sizeof(T);
	};

	template <>
	struct __total_size<> {
		static constexpr std::size_t value = 0;
	};

	template <typename... T>
	struct total_size {
		static constexpr std::size_t value = __total_size<T...>::value:
	};
}