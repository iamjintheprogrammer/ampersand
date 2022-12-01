#pragma once
#include <ampersand/extension/mysql/types.hpp>
#include <ampersand/extension/mysql/types_annotation.hpp>
#include <ampersand/extension/mysql/body.hpp>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

namespace ampersand::extension::mysql {
	template <meta::concepts::meta_type MetaType>
	class table
		: public meta::meta_object<mysql::body, MetaType> {
	public:
		using meta_type = MetaType;
		using name_type = std::string;

	public:
		template <typename... StringType>
		table(StringType&&... pName) {
			mysql::body::init_name_table
				(this->attribute_field(), std::make_tuple(pName...));
		}
	};

	template <typename MetaT, typename... StringType>
	auto make_table(MetaT&& pMeta, StringType&&... pString) {
		return 
			table<std::remove_reference_t<MetaT>>
					(std::forward<StringType>(pString)...);
	}
}