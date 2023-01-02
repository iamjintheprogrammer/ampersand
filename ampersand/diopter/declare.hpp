#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	template <meta::concepts::meta_object... MetaObject>
	class declare {
		using __tuple = std::tuple<MetaObject...>;
			  __tuple _M_Object;
	public:
		constexpr declare(MetaObject... pMeta) : _M_Object(pMeta) {}
	};

	template <meta::concepts::meta_type... MetaType>
	class type_declare {
		using __tuple = std::tuple<MetaType...>;
			  __tuple _M_Type;
	public:
		constexpr type_declare(MetaType... pMetaType) : _M_Type(pMetaType...) {}
	};
}

namespace ampersand::diopter::utility {
	template <typename... AnyType>
	struct is_declare					   : std::false_type {};
	template <typename... AnyType>
	struct is_declare<declare<AnyType...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_declare_v = is_declare<AnyType>::value;

	template <typename... AnyType>
	struct is_type_declare					    : std::false_type {};
	template <typename... AnyType>
	struct is_type_declare<declare<AnyType...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_type_declare_v = is_type_declare<AnyType>::value;
}

namespace ampersand::diopter::concepts {
	template <typename... AnyType>
	concept declare		 = utility::is_declare_v<AnyType...>;
	template <typename... AnyType>
	concept type_declare = utility::is_declare_v<AnyType...>;
}