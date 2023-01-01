#pragma once
#include <string>
#include <concepts>

namespace ampersand::poly::machine {
	class operand {
		enum class __category { object, primitive, constant, void_type };
				   __category _M_Category;
		
	public:
		class object {
			using __string_type = std::string;
				  __string_type _M_Type, _M_Name;
		public:
			using  string_type = __string_type;
			object(string_type, string_type);

		public:
			string_type&	  name();
			string_type& type_name();
		};

		class primitive {
			using	   __string_type = std::string;
			enum class __category {
				non_primitive,

				i8, i16, i32, i64,
				u8, u16, u32, u64,

				f32, f64, f128,
				str, wstr
			};
			__category    _M_Category;
			__string_type _M_Name;

		public:
			using category    = __category;
			using string_type = __string_type;
		public:
			template <typename InitArg> primitive(InitArg, string_type);
										primitive(const char*   , string_type);
										primitive(const wchar_t*, string_type);
										primitive(category		, string_type);
			category    get_category();
			string_type name		();
				  
		};

		class constant {
			using		   __size_type = std::size_t;
			enum class __constant_type {
				i8, i16, i32, i64,
				u8, u16, u32, u64,

				f32, f64, f128,
				str, wstr
			};
			__constant_type _M_Type		;
			__size_type	    _M_ValueSize;
			void*			_M_Value	;

		public:
			template <std::integral IntegralType>    constant(IntegralType);
			template <std::floating_point FloatType> constant(FloatType)   ;
													 constant(const char*)   ;
													 constant(const wchar_t*);
													 constant(const constant&);
													 constant(const constant&&);
													~constant();

		public:
			constant& operator=(const constant&);
			constant& operator=(const constant&&);

		public:
			using constant_type = __constant_type;
				  constant_type get_type ();
				  bool			get_value(std::int8_t &);
				  bool			get_value(std::uint8_t&);

				  bool			get_value(std::int16_t&);
				  bool			get_value(std::uint16_t&);

				  bool			get_value(std::int32_t&);
				  bool			get_value(std::uint32_t&);

				  bool			get_value(std::int64_t&);
				  bool			get_value(std::uint64_t&);

				  bool			get_value(float&) ;
				  bool			get_value(double&);
				  bool		    get_value(std::string&);
				  bool		    get_value(std::wstring&);
				  
				  std::string   get_string_value ();
				  std::wstring  get_wstring_value();
		};

	private:
		union {
			object   * _M_Operand_Object   ;
			primitive* _M_Operand_Primitive;
			constant * _M_Operand_Constant ;
		};
	public:
		using category	  = __category;
		using string_type = std::string;
												 operand(string_type, string_type)   ;		// Create Object
		template <typename PrimitiveValue>	     operand(PrimitiveValue, string_type);		// Create Primitive Value
												 operand(primitive::category, string_type); // Create Primitive Value
		template <std::integral IntegralType>    operand(IntegralType);
		template <std::floating_point FloatType> operand(FloatType)   ;
												 operand(const char*)   ;
												 operand(const wchar_t*);
												 operand();						   // Create Void Type
		explicit								 operand(const operand&) ;
		explicit								 operand(const operand&&);
												~operand();

		category operand_category();
		bool	 get_operand     (object  &) ;
		bool	 get_operand     (constant&) ;
		bool	 get_operand     (primitive&);
	};

	template <std::integral IntegralType>
	operand::constant::constant(IntegralType pValue) 
		: _M_Value	  (new IntegralType(pValue)),
		  _M_ValueSize(sizeof(IntegralType))    {
			if constexpr (std::is_same_v<IntegralType, std::int8_t>)
				_M_Type = constant_type::i8;
			if constexpr (std::is_same_v<IntegralType, std::uint8_t>)
				_M_Type = constant_type::u8;
			if constexpr (std::is_same_v<IntegralType, std::int16_t>)
				_M_Type = constant_type::i16;
			if constexpr (std::is_same_v<IntegralType, std::uint16_t>)
				_M_Type = constant_type::u16;
			if constexpr (std::is_same_v<IntegralType, std::int32_t>)
				_M_Type = constant_type::i32;
			if constexpr (std::is_same_v<IntegralType, std::uint32_t>)
				_M_Type = constant_type::u32;
			if constexpr (std::is_same_v<IntegralType, std::int64_t>)
				_M_Type = constant_type::i64;
			if constexpr (std::is_same_v<IntegralType, std::uint64_t>)
				_M_Type = constant_type::u64;
	}

	template <std::floating_point FloatType>
	operand::constant::constant(FloatType pValue)
		: _M_Value	  (new FloatType(pValue)),
		  _M_ValueSize(sizeof(FloatType))    {
			if constexpr (std::is_same_v<FloatType, float>)
				_M_Type = constant_type::f32;
			if constexpr (std::is_same_v<FloatType, double>)
				_M_Type = constant_type::f64;
	}

	template <std::integral IntegralType>
	operand::operand(IntegralType pValue)
		: _M_Operand_Constant(new operand::constant(pValue)),
		  _M_Category		 (category::constant)			{}

	template <std::floating_point FloatType>
	operand::operand(FloatType pValue)
		: _M_Operand_Constant(new operand::constant(pValue)),
		  _M_Category		 (category::constant)			{}

	template <typename InitArg>
	operand::operand
		(InitArg pInitArgument, string_type pName)
			: _M_Operand_Primitive(new primitive(pInitArgument, pName)),
			  _M_Category		  (category::primitive)				   {}

	template <typename InitArg>
	operand::primitive::primitive
		(InitArg pInitArgument, string_type pName) 
			: _M_Name(pName) {
		if constexpr (std::is_same_v<InitArg, std::int8_t>) {
			_M_Category = category::i8;
			return;
		}
		if constexpr (std::is_same_v<InitArg, std::uint8_t>) {
			_M_Category = category::u8;
			return;
		}

		if constexpr (std::is_same_v<InitArg, std::int16_t>) {
			_M_Category = category::i16;
			return;
		}
		if constexpr (std::is_same_v<InitArg, std::uint16_t>) {
			_M_Category = category::u16;
			return;
		}

		if constexpr (std::is_same_v<InitArg, std::int32_t>) {
			_M_Category = category::i32;
			return;
		}
		if constexpr (std::is_same_v<InitArg, std::uint32_t>) {
			_M_Category = category::u32;
			return;
		}

		if constexpr (std::is_same_v<InitArg, std::int64_t>) {
			_M_Category = category::i64;
			return;
		}
		if constexpr (std::is_same_v<InitArg, std::uint64_t>) {
			_M_Category = category::u64;
			return;
		}
	}
}