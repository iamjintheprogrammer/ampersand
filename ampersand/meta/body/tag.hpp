#pragma once
#include <ampersand/meta/body/tag_impl.hpp>

namespace ampersand::meta::body {
	struct tag {
		template <typename AnyType>
		struct attribute_field;

		template <typename... Attributes>
		struct attribute_field<meta::meta_type<Attributes...>> {
			using type = __tag_table<meta::meta_type<Attributes...>>;
		};

		template <typename MetaType>
		using attribute_field_type = attribute_field<MetaType>;

	public:
		template <typename FieldT, typename AttrT, typename MetaT>
        static auto&          get      (FieldT&&, AttrT, MetaT);
		
		template <typename FieldT, typename AttrT, typename MetaT>
        static auto&          get_name (FieldT&&, AttrT, MetaT);

        template <typename FieldT, typename AttrT, typename MetaT>
        static std::ptrdiff_t get_index(FieldT&&, AttrT, MetaT);
	};

	template <typename FieldT, typename AttrT, typename MetaT>
	auto&
		tag::get(FieldT&& pField, AttrT, MetaT) {
		return
			std::get
				<boost::mp11::mp_find
					<typename MetaT::type, AttrT>::value>
						(pField.attr_table);
	}

	template <typename FieldT, typename AttrT, typename MetaT>
	auto&
		tag::get_name(FieldT&& pField, AttrT, MetaT) {
		return
			std::get
				<boost::mp11::mp_find
					<typename MetaT::type, AttrT>::value>
						(pField.attr_name_table);
	}

	template <typename FieldT, typename AttrT, typename MetaT>
	std::ptrdiff_t
		tag::get_index(FieldT&& pField, AttrT, MetaT) {
		return
			boost::mp11::mp_find
				<typename MetaT::type, AttrT>::value;
	}
}