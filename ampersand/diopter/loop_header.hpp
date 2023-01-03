#pragma once
#include <ampersand/meta.hpp>

namespace ampersand::diopter {
	template <typename... AnyType>
	class loop_header;

	/*
	 * template 
	 *		<meta::concepts::meta_operator LoopCondition>
	 * class loop_header
	 * 
	 * --> Converted to while([LoopCondition])
	 * 
	 */
	template 
		<meta::concepts::conditional_operator LoopCondition>
	class loop_header<LoopCondition> {
		using __condition_type = LoopCondition;
			  __condition_type _M_Condition;
	public:
		using condition_type = LoopCondition;
		constexpr loop_header(condition_type pCond)
			: _M_Condition(pCond) {}

		condition_type& get_condition() { return _M_Condition; }
	};

	/*
	 * template 
	 *		<meta::concepts::meta_object LoopIterator,
	 *		 meta::concepts::meta_object LoopIterable>
	 * class loop_header
	 *
	 * --> Converted to Ranged For Syntax
	 *
	 */

	template 
		<meta::concepts::meta_object LoopIterator, meta::concepts::meta_object LoopIterable>
	class loop_header<LoopIterator, LoopIterable> {
		using __iterator_type = LoopIterator;
			  __iterator_type _M_Iterator;
		using __iterable_type = LoopIterable;
			  __iterable_type _M_Iterable;
	public:
		using iterator_type		   = LoopIterator;
		using iterable_object_type = LoopIterable;
		constexpr loop_header(iterator_type pIteartor, iterable_object_type pIterable)
			: _M_Iterator(pIteartor) ,
			  _M_Iterable(pIterable) {}

		iterator_type&		  get_iterator		 () { return _M_Iterator; }
		iterable_object_type& get_iterable_object() { return _M_Iterable; }
	};

	/*
	 * template 
	 *		<meta::concepts::meta_operator		  LoopIndex,
	 *		 meta::concepts::conditional_operator LoopCondition,
	 *		 meta::concepts::meta_operator		  LoopPostOperation>
	 * class loop_header
	 *
	 * --> Converted to Index Based For Syntax
	 *
	 */

	template 
		<meta::concepts::meta_operator		  LoopIndex	   ,
		 meta::concepts::conditional_operator LoopCondition,
		 meta::concepts::meta_operator		  LoopPostOperation>
	class loop_header<LoopIndex, LoopCondition, LoopPostOperation> {
		using __index_type			= LoopIndex;
			  __index_type			_M_Index;
		using __condition_type	    = LoopCondition;
			  __condition_type		_M_Condition;
		using __post_operation_type = LoopPostOperation;
			  __post_operation_type _M_PostOperation;
	public:
		using index_type		  = LoopIndex		 ;
		using condition_type	  = LoopCondition	 ;
		using post_operation_type = LoopPostOperation;

		constexpr loop_header
			(index_type		     pIndex		   ,
			 condition_type		 pCondition	   ,
			 post_operation_type pPostOperation) : _M_Index	       (pIndex)		  ,
												   _M_Condition	   (pCondition)	  ,
												   _M_PostOperation(pPostOperation) {}

		index_type&			 get_index		   () { return _M_Index		   ; }
		condition_type&		 get_condition	   () { return _M_Condition	   ; }
		post_operation_type& get_post_operation() { return _M_PostOperation; }
	};

	template <typename... LoopElement>
	loop_header(LoopElement...) -> loop_header<std::remove_reference_t<LoopElement...>>;

namespace utility {
	template <typename AnyType>
	struct is_loop_header						   : std::false_type {};
	template <typename... AnyType>
	struct is_loop_header<loop_header<AnyType...>> : std::true_type  {};
	template <typename... AnyType>
	inline constexpr bool is_loop_header_v = is_loop_header<AnyType...>::value;
}

namespace concepts {
	template <typename AnyType>
	concept loop_header = utility::is_loop_header_v<AnyType>;
}
}