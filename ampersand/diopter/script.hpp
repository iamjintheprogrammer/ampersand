#pragma once
#include <ampersand/diopter/condition.hpp>
#include <ampersand/diopter/loop.hpp>

#include <ampersand/diopter/syntax.hpp>
#include <ampersand/diopter/scope.hpp>

namespace ampersand::diopter {
namespace utility		     {
	template <typename AnyType>
	struct is_script_element
		: std::disjunction
			<
				utility::is_loop	 <AnyType>,
				utility::is_condition<AnyType>,

				meta::utility::is_meta_object  <AnyType>,
				meta::utility::is_meta_type    <AnyType>,
				meta::utility::is_meta_operator<AnyType>
			>{};

	template <typename AnyType>
	inline constexpr bool is_script_element_v = is_script_element<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept script_element = utility::is_script_element_v<AnyType>;
}

	class script {
		scope				_M_Impl_Scope ;
		std::vector<syntax> _M_Impl_Syntax;

										  void _M_Impl_Init(meta::concepts::meta_operator auto);
										  void _M_Impl_Init(meta::concepts::meta_type	  auto);
		template <typename T, typename U> void _M_Impl_Init(meta::basic_meta_object<T, U>&);

	public:
		class line {
			friend class script;
			std::vector<syntax>::iterator _M_Base;
			line(script&, bool);
		public:
			line&   operator++();
			line    operator++(int);
			syntax& operator* ();

			bool    operator==(line&);
			bool	operator!=(line&);
		};

	public:
		template <concepts::script_element... Elements>
		script(Elements...);

		line start_line();
		line end_line  ();
	};

	template <concepts::script_element... Elements>
	script::script(Elements... pElement) {
		((_M_Impl_Init(pElement)), ...);
	}

	void
		script::_M_Impl_Init
			(meta::concepts::meta_operator auto pOperator) {
		_M_Impl_Syntax.emplace_back(pOperator);
	}

	void
		script::_M_Impl_Init
			(meta::concepts::meta_type auto pMetaType) {
		auto& impl_symbol = _M_Impl_Scope.get_scoped_symbol();
			  impl_symbol.push_symbol(pMetaType);
	}

	template <typename T, typename U>
	void
		script::_M_Impl_Init
			(meta::basic_meta_object<T, U>& pObject) {
		auto& impl_stack = _M_Impl_Scope.get_scoped_stack();
		if constexpr (meta::utility::is_primitive_type_v<T>) {
			type   impl_type  (pObject.type_of());
			object impl_object(object::category::dynamic, pObject.name(), impl_type);

			impl_stack.push_object(impl_object);
		}
		else {
			auto impl_symbol = _M_Impl_Scope.get_scoped_symbol();
			auto impl_type   = impl_symbol.find_symbol(pObject.type_of().type_id());

			if (!impl_type) return;

			object impl_object(object::category::dynamic, pObject.name(), impl_type);
				   impl_stack.push_object(impl_object);
		}
		
	}

namespace utility {
	template <typename AnyType>
	struct is_script		 : std::false_type {};
	template <>
	struct is_script<script> : std::true_type  {};
	template <typename AnyType>
	inline constexpr bool is_script_v = is_script<AnyType>::value;
}

namespace concepts {
	template <typename AnyType>
	concept script = utility::is_script_v<AnyType>;
}
}