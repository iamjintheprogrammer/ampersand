#pragma once
#include <ampersand/extension/mysql/reader.hpp>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	class reader_iterator;

	template <typename BodyT, typename ParserType>
	class reader_iterator<reader<BodyT, ParserType>>
		: public 
			std::iterator
				<std::output_iterator_tag,
					typename reader<BodyT, ParserType>::value_type> {
		typename
			reader<BodyT, ParserType>::__result 
				_M_Iterator_Base;
	public:
		using value_type = typename reader<BodyT, ParserType>::value_type;

		reader_iterator(reader<BodyT, ParserType>& pResult) : _M_Iterator_Base(pResult._M_RdBase) {}
		reader_iterator()									: _M_Iterator_Base(nullptr)		      {}

	public:
		reader_iterator& operator++()   ;
		reader_iterator  operator++(int);
		value_type		 operator* ()   ;

		bool operator==(reader_iterator&);
		bool operator!=(reader_iterator&);
	};

	template <typename BodyT, typename ParserType>
	reader_iterator(reader<BodyT, ParserType>&)
		-> reader_iterator<reader<BodyT, ParserType>>;

	template <typename BodyT, typename ParserType>
	reader_iterator<reader<BodyT, ParserType>>&
		reader_iterator<reader<BodyT, ParserType>>::operator++() {
		if (!_M_Iterator_Base)						 return *this;
		if (!_M_Iterator_Base->next()) _M_Iterator_Base = nullptr;

		return *this;
	}

	template <typename BodyT, typename ParserType>
	reader_iterator<reader<BodyT, ParserType>>
		reader_iterator<reader<BodyT, ParserType>>::operator++(int) {
		if (!_M_Iterator_Base)						 return *this;
		if (!_M_Iterator_Base->next()) _M_Iterator_Base = nullptr;

		return *this;
	}

	template <typename BodyT, typename ParserType>
	reader_iterator<reader<BodyT, ParserType>>::value_type
		reader_iterator<reader<BodyT, ParserType>>::operator* () {
		value_type sql_result;

		__read(sql_result, _M_Iterator_Base);
		return sql_result;
	}

	template <typename BodyT, typename ParserType>
	bool
		reader_iterator<reader<BodyT, ParserType>>::operator==
			(reader_iterator<reader<BodyT, ParserType>>& pRhs) {
		return pRhs._M_Iterator_Base == _M_Iterator_Base;
	}

	template <typename BodyT, typename ParserType>
	bool
		reader_iterator<reader<BodyT, ParserType>>::operator!=
			(reader_iterator<reader<BodyT, ParserType>>& pRhs) {
		return pRhs._M_Iterator_Base != _M_Iterator_Base;
	}
}