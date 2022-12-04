#pragma once

#include <ampersand/meta/body/tuple.hpp>

#include <ampersand/extension/mysql/parser.hpp>
#include <ampersand/extension/mysql/connection.hpp>
#include <ampersand/extension/mysql/connection_base.hpp>

#include <iostream>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	struct __parser_value_metatype;

	template
		<typename StringType,
			typename TableType, typename... RowAttr, typename Condition>
	struct
		__parser_value_metatype
			<parser<StringType,
				schema::syntax::select<TableType,
					meta::meta_type<RowAttr...>, Condition>>> {
		using type = meta::meta_type<RowAttr...>;
	};

	template
		<typename StringType,
			typename TableType, typename... RowAttr>
	struct
		__parser_value_metatype
			<parser<StringType,
				schema::syntax::select<TableType, meta::meta_type<RowAttr...>>>> {
		using type = meta::meta_type<RowAttr...>;
	};

	template <std::size_t Index> 
	bool 
		__read_impl
			(sql::ResultSet* pResult, std::int32_t& pValue) {
		try											{ pValue = pResult->getInt(Index); }
		catch (sql::InvalidArgumentException& eSql) { return false; }
		return true;
	}

	template <std::size_t Index> 
	bool
		__read_impl
			(sql::ResultSet* pResult, std::int64_t& pValue) {
		try											{ pValue = pResult->getInt64(Index); }
		catch (sql::InvalidArgumentException& eSql) { return false; }
		return true;
	}

	template <std::size_t Index> 
	bool
		__read_impl
			(sql::ResultSet* pResult, std::uint32_t& pValue) {
		try											{ pValue = pResult->getUInt(Index); }
		catch (sql::InvalidArgumentException& eSql) { return false; }
		return true;
	}

	template <std::size_t Index> 
	bool
		__read_impl
			(sql::ResultSet* pResult, std::uint64_t& pValue) {
		try											{ pValue = pResult->getUInt64(Index); }
		catch (sql::InvalidArgumentException& eSql) { return false; }
		return true;
	}
	
	template <std::size_t Index> 
	bool
		__read_impl
			(sql::ResultSet* pResult, double& pValue) {
		try											{ pValue = pResult->getDouble(Index); }
		catch (sql::InvalidArgumentException& eSql) { return false; }
		return true;
	}

	template <typename BodyT, typename... Attribute>
	bool
		__read
			(meta::meta_object<BodyT, meta::meta_type<Attribute...>>& pObject,
			 sql::ResultSet*										  pResult) {
		bool result = true;
		[&pObject, &pResult, &result]<std::size_t... Idx>
			(std::index_sequence<Idx...>) {
				((result &= __read_impl<Idx + 1>(pResult, pObject
						[boost::mp11::mp_at_c
							<boost::mp11::mp_list<Attribute...>, Idx>{}])), ...);
		}(std::make_index_sequence<sizeof...(Attribute)>{});

		return result;
	}
}