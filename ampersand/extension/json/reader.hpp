#pragma once
#include <fstream>

#include <ampersand/meta/meta.hpp>
#include <ampersand/meta/body/tag.hpp>
#include <ampersand/meta/meta_object.hpp>

#include <ampersand/extension/json/reader_impl.hpp>

namespace ampersand::extension::json {
	template <typename... AnyType>
	class reader;

	template <typename BodyT, typename... AttrT>
	class reader<meta::meta_object<BodyT, meta::meta_type<AttrT...>>> {
		using  __rdobj    = Json::Value;
		using  __rdstr    = Json::String;
		using  __rdent	  = Json::CharReaderBuilder;
		using  __rdstream = std::ifstream;

		__rdent    _M_Reader;
		__rdstream _M_ReaderStream;
		
	public:
		using value_type = meta::meta_object<BodyT, meta::meta_type<AttrT...>>;
		reader (const char*);
		~reader()			{ _M_ReaderStream.close(); }

	public:
		value_type operator()();
	};

	template <typename BodyT, typename... AttrT>
	reader<meta::meta_object<BodyT, meta::meta_type<AttrT...>>>::reader
		(const char* pName)
			: _M_ReaderStream(pName),
			  _M_Reader	     ()	    { _M_Reader["collectComments"] = false; }

	template <typename BodyT, typename... AttrT>
	typename
		reader<meta::meta_object<BodyT, meta::meta_type<AttrT...>>>::value_type
			reader<meta::meta_object<BodyT, meta::meta_type<AttrT...>>>::operator()() {
			__rdobj json_object;
			__rdstr json_error_string;

			if (!Json::parseFromStream
					(_M_Reader, _M_ReaderStream, &json_object, &json_error_string))
						return false;

			__read_from(json_object, pObject);
			return true;
	}
}