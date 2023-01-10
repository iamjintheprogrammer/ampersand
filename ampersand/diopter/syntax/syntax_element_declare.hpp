#pragma once
#include <ampersand/diopter/syntax/syntax_element.hpp>

namespace ampersand::diopter::syntax {
	class type_declare : public element {
		using name_type_impl = std::string;
		name_type_impl impl_type_name;
	public:
		using name_type = name_type_impl;

		type_declare(meta::concepts::meta_impl auto);
		type_declare(meta::concepts::meta_type auto);

		name_type& type_name();
	};

	type_declare::type_declare
		(meta::concepts::meta_impl auto pMetaImpl)
			: impl_type_name(pMetaImpl.type_of().type_id())		,
			  element		(element_category_impl::type_declare) {}

	type_declare::type_declare
		(meta::concepts::meta_type auto pMetaType)
			: impl_type_name(pMetaType.type_of().type_id()),
			  element		(element_category_impl::type_declare) { }

	class object_declare : public element {
		using name_type_impl = std::string;
		name_type_impl			 impl_name			,
								 impl_type_name		;
		meta::primitive_category impl_type_primitive;
	public:
		using name_type = name_type_impl;

		object_declare(meta::concepts::primitive_object auto);
		object_declare(meta::concepts::compound_object  auto);

		name_type&				 type_name	   ();
		meta::primitive_category type_primitive();
		name_type&				 name		   ();
	};
}