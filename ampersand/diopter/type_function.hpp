#pragma once
#include <ampersand/diopter/type_compound.hpp>
#include <ampersand/diopter/type_primitive.hpp>

namespace ampersand::diopter {
	class function : public type {
		enum class  function_category_impl { function, method, static_method };
		using					 args_impl = std::unordered_map<type::name_type, type*>;
		args_impl impl_argument;
		type*	  impl_return  ,
				  impl_class   ;

		function(meta::concepts::function_type      auto&);
		function(meta::concepts::method_type	    auto&);
		function(meta::concepts::static_method_type auto&);

		template <typename C, typename R, typename... Args> void impl_init(meta::meta_type<C, R(Args...)>   &);
		template <typename C, typename R, typename... Args> void impl_init(meta::meta_type<C, R(C, Args...)>&);
		template			 <typename R, typename... Args> void impl_init(meta::meta_type<R(Args...)>&);

		template <std::size_t... Idx> void impl_init(meta::concepts::function_type      auto&, std::index_sequence<Idx...>);
		template <std::size_t... Idx> void impl_init(meta::concepts::method_type	    auto&, std::index_sequence<Idx...>);
		template <std::size_t... Idx> void impl_init(meta::concepts::static_method_type auto&, std::index_sequence<Idx...>);

		void impl_do_arg_init(meta::concepts::compound  auto&);
		void impl_do_arg_init(meta::concepts::primitive auto&);

		void impl_do_ret_init(meta::concepts::compound  auto&);
		void impl_do_ret_init(meta::concepts::primitive auto&);

	public:
		class argument_iterator {
			friend class function;
			using iter_impl = args_impl::iterator;
			
			iter_impl impl_arg_iterator;
			function& impl_function    ;
			type      impl_arg_error   { type::category::none };

			argument_iterator(function&, iter_impl);
		public:
			type&			   operator* ()   ;
			argument_iterator& operator++()   ;
			argument_iterator  operator++(int);

			bool				operator==(argument_iterator&);
			bool				operator!=(argument_iterator&);
		};

		using size_type			= args_impl::size_type;
		using name_type			= args_impl::key_type ;
		using function_category = function_category_impl;
		
		argument_iterator begin_argument();
		argument_iterator   end_argument();
		argument_iterator  find_argument(name_type);
		type&			     return_type();
	};

	function::function(meta::concepts::function_type      auto&);
	function::function(meta::concepts::method_type	    auto&);
	function::function(meta::concepts::static_method_type auto&);

	template <typename C, typename R, typename... Args>
	void
		function::impl_init
			(meta::meta_type<C, R(Args...)>& pMetaType) {
		impl_class = nullptr;
		impl_init(pMetaType, std::make_index_sequence<sizeof...(Args)>{});
	}

	template <typename C, typename R, typename... Args>
	void
		function::impl_init
			(meta::meta_type<C, R(C, Args...)>& pMetaType) {
		impl_class = nullptr;
		impl_init(pMetaType, std::make_index_sequence<sizeof...(Args)>{});
	}

	template <typename R, typename... Args>
	void
		function::impl_init
			(meta::meta_type<R(Args...)>& pMetaType) {
		impl_class = nullptr;
		impl_init(pMetaType, std::make_index_sequence<sizeof...(Args)>{});
	}

	template <std::size_t... Idx>
	void
		function::impl_init
			(meta::concepts::function_type auto& pMetaType, 
			 std::index_sequence<Idx...>) {
		  impl_do_ret_init(meta::get_return_type	   (pMetaType));
		((impl_do_arg_init(meta::get_argument_type<Idx>(pMetaType))), ...);
	}
	
	template <std::size_t... Idx>
	void
		function::impl_init
			(meta::concepts::method_type auto&, std::index_sequence<Idx...>) {
		  impl_do_ret_init(meta::get_return_type(pMetaType));
		((impl_do_arg_init(meta::get_argument_type<Idx>(pMetaType))), ...);
	}

	template <std::size_t... Idx>
	void
		function::impl_init
			(meta::concepts::static_method_type auto&, std::index_sequence<Idx...>) {
		  impl_do_ret_init(meta::get_return_type(pMetaType));
		((impl_do_arg_init(meta::get_argument_type<Idx>(pMetaType))), ...);
	}

	void
		function::impl_do_arg_init
			(meta::concepts::compound auto& pType) {
		impl_argument.insert
			(std::make_pair(pType.type_id(), nullptr));
	}

	void
		function::impl_do_arg_init
			(meta::concepts::primitive auto& pType) {
		impl_argument.insert
			(std::make_pair(pType, primitive(pType)));
	}

	void
		function::impl_do_ret_init
			(meta::concepts::compound auto& pType) {
		impl_return = nullptr;
	}

	void
		function::impl_do_ret_init
			(meta::concepts::primitive auto& pType) {
		impl_return = new primitive(pType);
	}
}