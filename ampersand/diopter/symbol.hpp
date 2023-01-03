#pragma once
#include <unordered_map>
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	class type {
	public:
		enum class			 category { primitive, complex };
		enum class primitive_category {
			i8 , u8 ,
			i16, u16,
			i32, u32,
			i64, u64,

			f32, f64,

			any
		};
	public:
		template <typename... T> type(meta::meta_type<T...>&);
								 type(meta::concepts::primitive auto&);

	public:
		bool link(const char*, type&);

	private:
		std::unordered_map<std::string, type*> _M_Table;
		category							   _M_Category;
		primitive_category					   _M_PrimitiveCategory;
	};

	template <typename... T>
	type::type(meta::meta_type<T...>& pMeta) {
		auto fn_init
			= [this, &pMeta]<std::size_t Idx>() {
				auto& attr		= meta::get_attribute<Idx>(pMeta);
				using attr_type = std::remove_reference_t<decltype(attr)>;

				if constexpr (meta::utility::is_primitive_attribute_v<attr_type>)
					_M_Table.insert
						(std::string(attr.name()),
						 new type   (attr.type()));
				else
					_M_Table.insert
						(std::string(attr.name()), nullptr);
			};
		
		[]<std::size_t... Idx>
			(std::index_sequence<Idx...>) { (fn_init<Idx>()...); }
				(std::make_index_sequence<sizeof...(T)>{});
	}

	type::type(meta::concepts::primitive auto& pMeta) {

	}
}