#pragma once
#include <cstdint>
#include <cstddef>

#include <tuple>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body/raw_impl.hpp>

namespace ampersand::meta::body {
	struct tuple {
		template <typename MetaType>
		struct attribute_field;

		template <typename... Attribute>
		struct attribute_field<meta_type<Attribute...>> {
			using type = std::tuple<typename Attribute::attribute_type...>;
		};

		template <typename MetaType>
		using attribute_field_type = typename attribute_field<MetaType>::type;

	public:
		template <typename FieldT, typename AttrT, typename MetaT>
		static auto&		  get	   (FieldT&&, AttrT, MetaT);
		template <typename FieldT, typename AttrT, typename MetaT>
		static std::ptrdiff_t get_index(FieldT&&, AttrT, MetaT);
	};

	template <typename FieldT, typename AttrT, typename MetaT>
	auto&
		tuple::get
			(FieldT&& pField, AttrT, MetaT) {
		return
			std::get
				<boost::mp11::mp_find
					<typename MetaT::type, AttrT>::value>
						(pField);
	}

	template <typename FieldT, typename AttrT, typename MetaT>
	std::ptrdiff_t
		tuple::get_index(FieldT&& pField, AttrT, MetaT) {
		return
			boost::mp11::mp_find
				<typename MetaT::type, AttrT>::value;
	}
}