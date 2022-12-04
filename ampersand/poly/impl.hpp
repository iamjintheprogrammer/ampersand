#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/meta/body/tag.hpp>
#include <string>

namespace ampersand::poly {
	template <typename... AnyType>
	class impl;

	template <typename... Attributes>
	class 
		impl<meta::meta_object
			<meta::body::tag<std::string>,
			 meta::meta_type<Attributes...>>>
				: meta::meta_object
					<meta::body::tag<std::string>,
					 meta::meta_type<Attributes...>>{
	public:
	};
}