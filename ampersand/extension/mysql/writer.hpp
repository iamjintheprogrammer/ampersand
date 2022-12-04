#pragma once

#include <ampersand/extension/mysql/driver.hpp>
#include <ampersand/extension/mysql/connection.hpp>

namespace ampersand::extension::mysql {
	template <typename... AnyType>
	class writer;

	template <typename BodyT, typename Parser>
	class writer<BodyT, Parser> {
	public:
		
	};
}