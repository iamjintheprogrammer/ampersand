#pragma once
#include <ampersand/schema/type_traits.hpp>
#include <ampersand/schema/syntax/select.hpp>

#include <ampersand/meta/condition.hpp>
#include <ampersand/meta/utility/trait.hpp>

namespace ampersand::extension::mysql {
	template
		<typename Table, typename LCond, typename RCond, typename StringType>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				meta::binary_condition
					<meta::greater_than, LCond, RCond>, StringType&& pParsed) {
		pParsed += pTable[LCond{}] + " > " 
				+  pTable[RCond{}];
	}

	template
		<typename Table, typename LCond, typename RCond, typename StringType>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				meta::binary_condition
					<meta::greater_or_equal, LCond, RCond>, StringType&& pParsed) {
		pParsed += pTable[LCond{}] + " >= "
				+  pTable[RCond{}];
	}

	template
		<typename Table, typename LCond, typename RCond, typename StringType>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				meta::binary_condition
					<meta::less_than, LCond, RCond>, StringType&& pParsed) {
		pParsed += pTable[LCond{}] + " < "
				+  pTable[RCond{}];
	}

	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				meta::binary_condition
					<meta::less_or_equal, LCond, RCond>, std::string& pParsed) {
		pParsed += pTable[LCond{}] + " <= " 
				+  pTable[RCond{}];
	}

	template
		<typename Table, typename LCond, typename RCond, typename StringType>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				meta::binary_condition
					<meta::equal_with, LCond, RCond>, StringType&& pParsed) {
		pParsed += pTable[LCond{}] + " = " 
				+  pTable[RCond{}];
	}

	template
		<typename Table, typename LCond, typename RCond, typename StringType>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				meta::binary_condition
					<meta::different_with, LCond, RCond>, StringType&& pParsed) {
		pParsed += pTable[LCond{}] + " != " 
				+  pTable[RCond{}];
	}

	template
		<typename Table, typename CondVerb, typename LCond, typename RCond, typename StringType>
	void
		__parse_binary_condition
			(Table&&										pTable	  ,
			 meta::binary_condition<CondVerb, LCond, RCond> pCondition,
				StringType&&								pParsed)  {
		if constexpr (meta::utility::is_binary_condition_v<LCond>) {
			pParsed += "(";
			__parse_binary_condition(pTable, LCond{}, pParsed);
			pParsed += ")";

			if constexpr (std::is_same_v<CondVerb, meta::and_with>)
				pParsed += " and ";
			if constexpr (std::is_same_v<CondVerb, meta::or_with>)
				pParsed += " or ";

			pParsed += "(";
			__parse_binary_condition(pTable, RCond{}, pParsed);
			pParsed += ")";
		}
		else
			__parse_binary_condition_impl(pTable, pCondition, pParsed);
	}
}