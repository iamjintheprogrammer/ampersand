#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	class table;

	template <meta::concepts::primitive_attribute... Attr>
	class table<meta::meta_type<Attr...>> {
		using __base_type = meta::meta_type<Attr...>;
			  __base_type _M_BaseType;
	public:
		using base_type = meta::meta_type<Attr...>;
		table(base_type&);
		
	public:
		template <typename BodyTrait> void		  push	(meta::basic_meta_object<base_type, BodyTrait>&);
									  void		  update(meta::concepts::meta_operator auto, meta::concepts::copy auto...);
									  void		  pop	(meta::concepts::meta_operator auto);
									  const char* name  ();
	};

	template <meta::concepts::primitive_attribute... Attr>
	table<meta::meta_type<Attr...>>::table
		(base_type& pBaseType)
			: _M_BaseType(pBaseType) {}
	
	template <meta::concepts::primitive_attribute... Attr>
	template <typename BodyTrait>
	void 
		table<meta::meta_type<Attr...>>::push
			(meta::basic_meta_object<base_type, BodyTrait>& pPush) {
		
	}

	template <meta::concepts::primitive_attribute... Attr>
	void 
		table<meta::meta_type<Attr...>>::update
			(meta::concepts::meta_operator auto pCondition,
			 meta::concepts::copy auto...		pCopy) {
	}

	template <meta::concepts::primitive_attribute... Attr>
	void 
		table<meta::meta_type<Attr...>>::pop
			(meta::concepts::meta_operator auto pCondition) {
	}

	template <meta::concepts::primitive_attribute... Attr>
	const char*
		table<meta::meta_type<Attr...>>::name() {
			return
				_M_BaseType.type_name();
	}
}

namespace ampersand::schema::utility {
	template <typename... AnyType>
	struct is_table									 : std::false_type {};
	template <meta::concepts::primitive_attribute... Attr>
	struct is_table<table<meta::meta_type<Attr...>>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_table_v = is_table<AnyType...>::value;
}

namespace ampersand::schema::concepts {
	template <typename... AnyType>
	concept table = utility::is_table_v<AnyType...>;
}