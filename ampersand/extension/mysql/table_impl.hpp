#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <tuple>
#include <string>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	struct __table_name_tuple_impl;

	template <typename AttrT, typename... Remaining, typename... TupleType>
	struct 
		__table_name_tuple_impl
			<std::tuple<TupleType...>, AttrT, Remaining...> {
		using type 
			= __table_name_tuple_impl
					<std::tuple<TupleType..., std::string>,
						Remaining....>::type;
	};

	template <typename AttrT, typename... TupleType>
	struct
		__table_name_tuple_impl
			<std::tuple<TupleType...>, AttrT> {
		using type = std::tuple<TupleType..., std::string>;
	};

	template <typename... AttrT>
	struct __table_name_tuple {
		using type
			= typename __table_name_tuple_impl
					<std::tuple<>, AttrT...>::type;
	};

	template <typename AttrT, typename... MetaAttribute, typename TupleType>
	auto& 
		__name_from_tuple
			(AttrT, meta::meta_type<MetaAttribute...>, TupleType&& pTuple) {
		return
			std::get
				<boost::mp11::mp_find
					<boost::mp11::mp_list<MetaAttribute...>, AttrT>::value>
						(pTuple);
	}
}