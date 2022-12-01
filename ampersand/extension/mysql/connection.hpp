#pragma once
#include <ampersand/extension/mysql/driver.hpp>
#include <ampersand/extension/mysql/connection_base.hpp>

namespace ampersand::extension::mysql {
	class connection : public connection_base {
		template <typename... AnyType> friend class table;
		template <typename... AnyType> friend class reader;
		template <typename... AnyType> friend class writer;
	public:
		using string_type = std::string;
		using endpoint	  = connection_base::endpoint;
	public:
		 connection(driver&, endpoint, string_type);
		~connection();
	};
}