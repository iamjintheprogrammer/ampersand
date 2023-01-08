#pragma once
#include <unordered_map>
#include <ampersand/diopter/type.hpp>
#include <ampersand/diopter/type_primitive.hpp>

namespace ampersand::diopter {
	class compound : public type {
		using table_impl = std::unordered_map<name_impl, type*>;

		type       impl_error		  { type::category::none };
		table_impl impl_attribute	  ,
				   impl_nested_declare;

		compound(meta::concepts::compound auto);
													 void impl_do_init(meta::concepts::compound  auto); // Nested Declared
													 void impl_do_init(meta::concepts::attribute auto);
		template <std::size_t... Idx, typename... T> void impl_init   (meta::meta_type<T...>&, std::index_sequence<Idx...>);
		template					 <typename... T> void impl_init   (meta::meta_type<T...>&);
	public:
		using size_type = table_impl::size_type;
		using name_type = table_impl::key_type ;

		class attribute_iterator {
			friend class compound;
			using iter_impl = table_impl::iterator;
			      compound& impl_compound;
				  iter_impl impl_value_iterator;
				  type		impl_value_error   { type::category::none };

			attribute_iterator(compound&, iter_impl);
		public:
			type&				operator* ()   ;
			attribute_iterator& operator++()   ;
			attribute_iterator  operator++(int);

			bool				operator==(attribute_iterator&);
			bool				operator!=(attribute_iterator&);
		};

		class nested_declare_iterator {
			friend class compound;
			using iter_impl = table_impl::iterator;
				  compound& impl_compound;
				  iter_impl impl_value_iterator;
				  type		impl_value_error   { type::category::none };

			nested_declare_iterator(compound&, iter_impl);
		public:
			type&					 operator* ()   ;
			nested_declare_iterator& operator++()   ;
			nested_declare_iterator  operator++(int);

			bool				operator==(nested_declare_iterator&);
			bool				operator!=(nested_declare_iterator&);
		};

		size_type		   attribute_count();
		attribute_iterator begin_attribute();
		attribute_iterator   end_attribute();
		type&				find_attribute(name_type);

		size_type				nested_declare_count();
		nested_declare_iterator begin_nested_declare();
		nested_declare_iterator   end_nested_declare();
		type&				     find_nested_declare(name_type);
	};

	compound::compound
		(meta::concepts::compound auto pCompound)
			: type(pCompound.type_id(), category_impl::compound) {}

	void
		compound::impl_do_init
			(meta::concepts::compound auto pCompound) {
		impl_nested_declare.insert
			(std::make_pair(pCompound.type_id(), new compound(pCompound)));
	}

	void
		compound::impl_do_init
			(meta::concepts::attribute auto pAttribute) {
		if constexpr
			(meta::utility::is_primitive_attribute_v<decltype(pAttribute)>)
				impl_attribute.insert
					(std::make_pair(pAttribute.name(), 
						new primitive(pAttribute.type().type_id())));
		else
			impl_attribute.insert
				(std::make_pair(pAttribute.name(), nullptr));
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