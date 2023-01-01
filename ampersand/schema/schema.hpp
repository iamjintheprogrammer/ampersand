#pragma once
#include <ampersand/meta.hpp>
#include <ampersand/schema/table.hpp>

namespace ampersand::schema {
	template <typename... AnyType>
	class schema;

	template <meta::concepts::attribute... Attr>
	class schema<meta::meta_type<Attr...>> {
		using __tuple	  = std::tuple<table<typename Attr::value_type>...>;
			  __tuple     _M_Tuple;
		using __base_type = meta::meta_type<Attr...>;
			  __base_type _M_BaseType;
	public:
		using base_type = meta::meta_type<Attr...>;
		schema(base_type&);
		
		auto operator[](concepts::table auto);
	};
}