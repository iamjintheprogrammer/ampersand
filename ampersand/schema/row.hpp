#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>
#include <ampersand/meta/body/tuple.hpp>

#include <ampersand/schema/field.hpp>

namespace ampersand::schema {
	template
		<typename... FieldType>
	struct row : meta::meta_type<typename FieldType::field_meta_type...> {
		using row_meta_type = meta::meta_type<typename FieldType::field_meta_type...>;

		row() {}
		row(FieldType...)
			: meta::meta_type<typename FieldType::field_meta_type...>() {}
	};

	template
		<typename... MetaType>
	struct row<meta::meta_type<MetaType...>>
		: meta::meta_type<MetaType...> {
		using row_meta_type = meta::meta_type<MetaType...>;

		row() {}
		row(meta::meta_type<MetaType...>...)
			: meta::meta_type<MetaType...>() {}
	};

	template <typename... FieldType>
	row(FieldType...) -> row<FieldType...>;

	template <typename... MetaType>
	row(meta::meta_type<MetaType...>) -> row<meta::meta_type<MetaType...>>;
}