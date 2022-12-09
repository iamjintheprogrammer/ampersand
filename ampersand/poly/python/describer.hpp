#pragma once
#include <ampersand/poly/python/describer_unit.hpp>

namespace ampersand::poly::python {
	template <typename StringType = std::string>
	class describer {
	public:
		using string_type = StringType;
	public:
		string_type describe	 (fetch_line&);
		string_type describe_once(fetch_line&);
	};

	template <typename StringType>
	typename describer<StringType>::string_type
		describer<StringType>::describe(fetch_line& pLine) {
		string_type str_return;

		while (pLine.parse_next()) {
			string_type str_line;
			auto it_begin = pLine.begin_point();
			auto it_end   = pLine.end_point  ();

			for (;   it_begin != it_end
				 ; ++it_begin) {
				describer_unit
					((*it_begin).verb(), (*it_begin), str_line);
			}
			str_return += str_line + "\n";
		}

		return str_return;
	}

	template <typename StringType>
	typename describer<StringType>::string_type
		describer<StringType>::describe_once(fetch_line& pLine) {
		string_type str_return;
		auto it_begin = pLine.begin_point();
		auto it_end   = pLine.end_point  ();

		for (;   it_begin != it_end
			 ; ++it_begin) {
			describer_unit
				((*it_begin).verb(), (*it_begin), str_return);
		}

			   str_return += "\n";
		return str_return;
	}
}