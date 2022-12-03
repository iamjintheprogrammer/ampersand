#pragma once
#include <ampersand/schema/type_traits.hpp>
#include <ampersand/schema/select.hpp>

namespace ampersand::extension::mysql {
	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				schema::syntax::binary_condition
					<schema::syntax::larger_than, LCond, RCond>,
						std::string& pParsed) {
		pParsed += pTable[typename LCond::field_meta_type {}] + " > " 
				+  pTable[typename RCond::field_meta_type {}];
	}

	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				schema::syntax::binary_condition
					<schema::syntax::larger_or_equal, LCond, RCond>,
						std::string& pParsed) {
		pParsed += pTable[typename LCond::field_meta_type {}] + " >= " 
				+  pTable[typename RCond::field_meta_type {}];
	}

	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				schema::syntax::binary_condition
					<schema::syntax::less_than, LCond, RCond>,
						std::string& pParsed) {
		pParsed += pTable[typename LCond::field_meta_type {}] + " < " 
				+  pTable[typename RCond::field_meta_type {}];
	}

	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				schema::syntax::binary_condition
					<schema::syntax::less_or_equal, LCond, RCond>,
						std::string& pParsed) {
		pParsed += pTable[typename LCond::field_meta_type {}] + " <= " 
				+  pTable[typename RCond::field_meta_type {}];
	}

	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				schema::syntax::binary_condition
					<schema::syntax::equal_with, LCond, RCond>,
						std::string& pParsed) {
		pParsed += pTable[typename LCond::field_meta_type {}] + " = " 
				+  pTable[typename RCond::field_meta_type {}];
	}

	template
		<typename Table, typename LCond, typename RCond>
	void
		__parse_binary_condition_impl
			(Table&& pTable,
				schema::syntax::binary_condition
					<schema::syntax::different_with, LCond, RCond>,
						std::string& pParsed) {
		pParsed += pTable[typename LCond::field_meta_type {}] + " != " 
				+  pTable[typename RCond::field_meta_type {}];
	}

	template
		<typename Table, typename CondVerb, typename LCond, typename RCond>
	void
		__parse_binary_condition
			(Table&&												  pTable	,
			 schema::syntax::binary_condition<CondVerb, LCond, RCond> pCondition,
			 std::string&											  pParsed)  {
		if constexpr (schema::is_binary_condition_v<LCond>) {
			pParsed += "(";
			__parse_binary_condition(pTable, LCond{}, pParsed);
			pParsed += ")";

			if constexpr (std::is_same_v<CondVerb, schema::syntax::and_with>)
				pParsed += " and ";
			if constexpr (std::is_same_v<CondVerb, schema::syntax::or_with>)
				pParsed += " or ";

			pParsed += "(";
			__parse_binary_condition(pTable, RCond{}, pParsed);
			pParsed += ")";
		}
		else
			__parse_binary_condition_impl(pTable, pCondition, pParsed);
	}
}