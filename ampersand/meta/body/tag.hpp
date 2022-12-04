#pragma once
#include <ampersand/meta/body/tag_impl.hpp>

namespace ampersand::meta::body {
	template <typename KeyType>
	struct tag {
		template <typename AnyType>
		struct attribute_field;

		template <typename... Attributes>
		struct attribute_field<meta_type<Attributes...>> {
			using type = __tag_table<KeyType, meta_type<Attributes...>>;
		};

		template <typename MetaType>
		using attribute_field_type = typename attribute_field<MetaType>::type;

	public:
		template <typename MetaT, typename FieldT, typename AttrT>
        static auto&		  get       (FieldT&&, AttrT);
		template <typename MetaT, typename FieldT, typename AttrT>
		static auto&		  get_key   (FieldT&&, AttrT);
		template <typename MetaT, typename FieldT, typename AttrT>
        static std::ptrdiff_t get_index (FieldT&&, AttrT);
	};

	template <typename KeyType>
	template <typename MetaT, typename FieldT, typename AttrT>
	auto& 
		tag<KeyType>::get
			(FieldT&& pField, AttrT pAttr) {
		static_assert
			(boost::mp11::mp_find
				<typename __tag_meta_to_mp11<MetaT>::type, AttrT>::value
					!= __tag_meta_to_mp11<MetaT>::count,
						"[AMPERSAND::META::TAG] Undefined Attribute Access");
		return
			std::get
				<boost::mp11::mp_find
					<typename __tag_meta_to_mp11<MetaT>::type, AttrT>::value>
						(pField.attr_table);
	}

	template <typename KeyType>
	template <typename MetaT, typename FieldT, typename AttrT>
	auto&
		tag<KeyType>::get_key
			(FieldT&& pField, AttrT pAttr) {
		static_assert
			(boost::mp11::mp_find
				<typename __tag_meta_to_mp11<MetaT>::type, AttrT>::value
					!= __tag_meta_to_mp11<MetaT>::count,
						"[AMPERSAND::META::TAG] Undefined Attribute Access");
		return
			std::get
				<boost::mp11::mp_find
					<typename __tag_meta_to_mp11<MetaT>::type, AttrT>::value>
						(pField.attr_name_table);
	}

	template <typename KeyType>
	template <typename MetaT, typename FieldT, typename AttrT>
	std::ptrdiff_t
		tag<KeyType>::get_index
			(FieldT&& pField, AttrT pAttribute) {
		return
			boost::mp11::mp_find
				<typename __tag_meta_to_mp11<MetaT>::type, AttrT>::value;
	}
}

namespace ampersand::meta { 
	template <typename KeyType>
	inline constexpr body::tag<KeyType> tag_body = body::tag<KeyType>{}; 
}