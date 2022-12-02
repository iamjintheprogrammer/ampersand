#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>
#include <ampersand/meta/body/tuple.hpp>

#include <ampersand/schema/field.hpp>

namespace ampersand::schema {
	template
		<typename BodyT, typename... FieldType>
	struct row : meta::meta_type<typename FieldType::field_meta_type...> {
		using row_meta_type = meta::meta_type<typename FieldType::field_meta_type...>;

		row() {}
		row(BodyT, FieldType...)
			: meta::meta_type<typename FieldType::field_meta_type...>() {}
	};

	template <typename BodyT, typename... FieldType>
	row(BodyT, FieldType...) -> row<BodyT, FieldType...>;
}