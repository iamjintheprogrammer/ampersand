#pragma once
#include <memory>
#include <unordered_map>

#include <ampersand/diopter/type.hpp>
#include <ampersand/diopter/type_primitive.hpp>

namespace ampersand::diopter {
	class compound : public type {
		friend class symbol;
		using table_impl  = std::unordered_map<name_impl, std::shared_ptr<type>>;

		type			  impl_error		 { type::category::none };
		table_impl		  impl_attribute	 ,
						  impl_nested_declare;
		compound*		  impl_nested_super  ;

		compound		   (meta::concepts::compound auto);
		compound(compound&, meta::concepts::compound auto);
													 void impl_do_init(meta::concepts::compound  auto); // Nested Declared
													 void impl_do_init(meta::concepts::compound_attribute  auto);
													 void impl_do_init(meta::concepts::primitive_attribute auto);
		template <std::size_t... Idx, typename... T> void impl_init   (meta::meta_type<T...>&, std::index_sequence<Idx...>);
		template					 <typename... T> void impl_init   (meta::meta_type<T...>&);
		
		static std::shared_ptr<type> impl_find_type			   (compound&, name_type);
		static std::shared_ptr<type> impl_find_type_from_super (compound&, name_type);
		static std::shared_ptr<type> impl_find_type_from_nested(compound&, name_type);
		static std::shared_ptr<type> impl_find_type_from_all   (compound&, name_type);
	public:
		using size_type = table_impl::size_type;
		using name_type = table_impl::key_type ;

		class attribute;
		class nested_declare;

		type& get_super();

	public:
		static type& find_type	          (compound&, name_type);
		static type& find_type_from_super (compound&, name_type);
		static type& find_type_from_nested(compound&, name_type);
		static type& find_type_from_all   (compound&, name_type);
	};

	compound::compound
		(meta::concepts::compound auto pCompound)
			: type			   (pCompound.type_id(), category_impl::compound),
			  impl_nested_super(nullptr) {
		impl_init(pCompound);
	}

	compound::compound
		(compound& pSuper, meta::concepts::compound auto pCompound)
			: type			   (pCompound.type_id(), category_impl::compound),
			  impl_nested_super(pSuper) {
		impl_init(pCompound);
	}

	void
		compound::impl_do_init
			(meta::concepts::compound auto pCompound) {
		impl_nested_declare.insert
			(std::make_pair
				(pCompound.type_id(),
					std::shared_ptr<compound>(new compound(*this, pCompound))));
	}

	void
		compound::impl_do_init
			(meta::concepts::compound_attribute auto pAttribute) {
		type& type_from_current = compound::find_type(*this, pAttribute.type_of().type_id());
		if (type_from_current.type_category() != type::category::none) {
			impl_attribute.insert
				(std::make_pair(pAttribute.name(),
					std::shared_ptr<type>(&type_from_current)));
			return;
		}

		type& type_from_super = compound::find_type_from_super(*this, pAttribute.type_of().type_id());
		if (type_from_super.type_category() != type::category::none) {
			impl_attribute.insert
				(std::make_pair(pAttribute.name(),
					std::shared_ptr<type>(&type_from_current)));
			return;
		}

		impl_attribute.insert
			(std::make_pair(pAttribute.name(),
				std::shared_ptr<type>(nullptr)));
	}

	void
		compound::impl_do_init
			(meta::concepts::primitive_attribute auto pAttribute) {
		impl_attribute.insert
			(std::make_pair(pAttribute.name(), std::shared_ptr<type>(new primitive(pAttribute.type().type_id()))));
	}

	template <std::size_t... Idx, typename... T>
	void
		compound::impl_init
			(meta::meta_type<T...>& pMeta, std::index_sequence<Idx...>) {
		((impl_do_init(meta::get_attribute<Idx>(pMeta))), ...);
	}

	template <typename... T>
	void
		compound::impl_init
			(meta::meta_type<T...>& pMeta) {
		impl_init(pMeta, std::make_index_sequence<sizeof...(T)>{});
	}
}