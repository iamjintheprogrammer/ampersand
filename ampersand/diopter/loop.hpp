#pragma once
#include <ampersand/meta.hpp>
#include <ampersand/diopter/scope.hpp>

namespace ampersand::diopter {
	template <typename... AnyType>
	class loop;

	template
		<meta::concepts::conditional_operator Condition,
		 concepts::scope					  Scope>
	class loop<Condition, Scope> {
		using __condition_type = Condition;
		using	  __scope_type = Scope;

		__condition_type _M_Condition;
		__scope_type	 _M_Scope	 ;
	public:
		loop(Condition pCond, Scope pScope)
			: _M_Condition(pCond),
			  _M_Scope	  (pScope) {}
	};

	template
		<concepts::declare					  InitDeclare  ,
		 meta::concepts::conditional_operator Condition    ,
		 meta::concepts::meta_operator		  PostOperation,
		 concepts::scope					  Scope>
	class loop<InitDeclare, Condition, PostOperation, Scope> {
		InitDeclare   _M_Init		  ;
		Condition     _M_Condition	  ;
		PostOperation _M_PostOperation;
		Scope		  _M_Scope		  ;
	public:
		loop
			(InitDeclare   pInit		 ,
			 Condition     pCond		 ,
			 PostOperation pPostOperation,
			 Scope		   pScope)		 : _M_Condition(pCond),
										   _M_Scope	   (pScope) {}
	};

	template
		<meta::concepts::conditional_operator Condition,
		 concepts::scope					  Scope>
	loop(Condition, Scope) -> loop<Condition, Scope>;
		
}