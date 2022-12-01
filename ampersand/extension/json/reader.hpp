#pragma once
#include <fstream>

#include <ampersand/meta/meta.hpp>
#include <ampersand/extension/json/reader_impl.hpp>

namespace ampersand::extension::json {
	class reader {
		using  __rdobj    = Json::Value;
		using  __rdstr    = Json::String;
		using  __rdent	  = Json::CharReaderBuilder;
		using  __rdstream = std::ifstream;

		__rdent    _M_Reader;
		__rdstream _M_ReaderStream;
		
	public:
		reader(const char* pName)
				  : _M_ReaderStream(pName),
				    _M_Reader	   ()	  {
			_M_Reader["collectComments"] = false;
		}
		~reader() { _M_ReaderStream.close(); }

	public:
		template <typename MetaObject>
		bool read_from(MetaObject&);
	};

	template <typename MetaObject>
	bool 
		reader::read_from(MetaObject& pObject) {
			__rdobj json_object;
			__rdstr json_error_string;

			if (!Json::parseFromStream
					(_M_Reader, _M_ReaderStream, &json_object, &json_error_string))
						return false;

			__read_from(json_object, pObject);
			return true;
	}
}