#pragma once
#include <cstdint>
#include <cstddef>

#include <tuple>

#include <ampersand/meta/utility/trait.hpp>
#include <ampersand/meta/utility/trait_concept.hpp>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body/raw_impl.hpp>

#include <ampersand/meta/body/tuple_impl.hpp>

namespace ampersand::meta::body {
	struct tuple {
		template <typename MetaType>
		struct attribute_field;

		template <typename... Attribute>
		struct attribute_field<meta_type<Attribute...>> {
			using type = std::tuple<typename Attribute::value_type...>;
		};

		template <typename MetaType>
		using attribute_field_type = typename attribute_field<MetaType>::type;

	public:
		template <typename MetaT, typename FieldT, typename AttrT>
		static constexpr auto&		  get	     (FieldT&&, AttrT);
		template <typename MetaT, typename FieldT, typename AttrT>
		static constexpr std::ptrdiff_t get_index(FieldT&&, AttrT);
	};

	template <typename MetaT, typename FieldT, typename AttrT>
	constexpr auto&
		tuple::get(FieldT&& pField, AttrT) {
		return
			std::get
				<boost::mp11::mp_find
					<typename __tuple_meta_to_mp11<MetaT>::type, AttrT>::value>
						(pField);
	}

	template <typename MetaT, typename FieldT, typename AttrT>
	constexpr std::ptrdiff_t
		tuple::get_index(FieldT&& pField, AttrT) {
		return
			boost::mp11::mp_find
				<typename __tuple_meta_to_mp11<MetaT>::type, AttrT>::value;
	}
}

namespace ampersand::meta { inline constexpr body::tuple tuple_body = body::tuple{}; }