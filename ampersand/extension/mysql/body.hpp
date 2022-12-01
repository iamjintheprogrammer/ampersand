#pragma once
#include <ampersand/meta/meta.hpp>
#include <ampersand/extension/mysql/body_impl.hpp>

namespace ampersand::extension::mysql {
	struct body {
	public:
		template <typename... AnyTypes>
		struct attribute_field;

		template <typename... AnyTypes>
		struct attribute_field_impl;

		template <typename... Attributes>
		struct attribute_field_impl<meta::meta_type<Attributes...>> {
			using __name_tuple = typename __name_tuple_from_meta<Attributes...>::type;
			using	   __tuple = std::tuple<typename Attributes::attribute_type...>;

			__name_tuple name_table;
				 __tuple	  table;
		};

		template <typename... Attributes>
		struct attribute_field<meta::meta_type<Attributes...>> {
			using type = attribute_field_impl<meta::meta_type<Attributes...>>;
		};

		template <typename MetaType>
		using attribute_field_type = typename attribute_field<MetaType>::type;

	public:
		template <typename FieldT, typename AttrT, typename MetaT>
		static auto& get(FieldT&& pField, AttrT, MetaT) {
			return
				std::get
					<boost::mp11::mp_find
						<typename MetaT::type, AttrT>::value>
							(pField.table);
		}

		template <typename FieldT, typename AttrT, typename MetaT>
		static auto& get_name(FieldT&& pField, AttrT, MetaT) {
			return
				std::get
					<boost::mp11::mp_find
						<typename MetaT::type, AttrT>::value>
							(pField.name_table);
		}

		template <typename FieldT, typename NameTuple>
		static void init_name_table(FieldT&& pField, NameTuple&& pNameTuple) {
			pField.name_table = pNameTuple;
		}
	};
}