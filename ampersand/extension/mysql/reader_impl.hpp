#pragma once

#include <ampersand/meta/body/tuple.hpp>

#include <ampersand/extension/mysql/table.hpp>
#include <ampersand/extension/mysql/table_impl.hpp>

#include <ampersand/extension/mysql/connection.hpp>
#include <ampersand/extension/mysql/connection_base.hpp>

namespace ampersand::extension::mysql {
	template <std::size_t Index> 
	void 
		__read_impl
			(sql::ResultSet* pResult, std::int32_t& pValue) {
		pValue = pResult->getInt(Index);
	}

	template <std::size_t Index> 
	void 
		__read_impl
			(sql::ResultSet* pResult, std::int64_t& pValue) {
		pValue = pResult->getInt64(Index);
	}

	template <std::size_t Index> 
	void 
		__read_impl
			(sql::ResultSet* pResult, std::uint32_t& pValue) {
		pValue = pResult->getUInt(Index);
	}

	template <std::size_t Index> 
	void 
		__read_impl
			(sql::ResultSet* pResult, std::uint64_t& pValue) {
		pValue = pResult->getUInt64(Index);
	}
	
	template <std::size_t Index> 
	void 
		__read_impl
			(sql::ResultSet* pResult, double& pValue) {
		pValue = pResult->getDouble(Index);
	}

	template <typename... Attribute>
	void
		__read
			(meta::meta_object
				<meta::body::tuple,
					meta::meta_type<Attribute...>>& pObject,
			 sql::ResultSet*					    pResult) {
		[&pObject, &pResult]<std::size_t... Idx>
			(std::index_sequence<Idx...>) {
				(( __read_impl<Idx>
					(pResult, pObject
						[boost::mp11::mp_at_c
							<boost::mp11::mp_list<Attribute...>, Idx>{}])), ...);
		}(std::make_index_sequence<sizeof...(Attribute)>{});
	}
}