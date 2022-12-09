#pragma once
#include <string>
#include <concepts>

namespace ampersand::poly::machine {
	class operand {
		enum class __category { object, constant, void_type };
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
			template <std::integral IntegralType>    constant(IntegralType&&);
			template <std::floating_point FloatType> constant(FloatType&&)   ;
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
			object  * _M_Operand_Object  ;
			constant* _M_Operand_Constant;
		};
	public:
		using category	  = __category;
		using string_type = std::string;
												 operand(string_type, string_type); // Create Object
		template <std::integral IntegralType>    operand(IntegralType&&);
		template <std::floating_point FloatType> operand(FloatType&&)   ;
												 operand(const char*)   ;
												 operand(const wchar_t*);
												 operand();						   // Create Void Type
		explicit								 operand(const operand&) ;
		explicit								 operand(const operand&&);
												~operand();

		category operand_category();
		bool	 get_operand     (object  &);
		bool	 get_operand     (constant&);
	};

	template <std::integral IntegralType>
	operand::constant::constant(IntegralType&& pValue) 
		: _M_Value(new operand::constant(pValue)) {}

	template <std::floating_point FloatType>
	operand::constant::constant(FloatType&& pValue)
		: _M_Value(new operand::constant(pValue)) {}

	template <std::integral IntegralType>
	operand::operand(IntegralType&& pValue)
		: _M_Operand_Constant(new operand::constant(pValue)),
		  _M_Category		 (category::constant)			{}

	template <std::floating_point FloatType>
	operand::operand(FloatType&& pValue)
		: _M_Operand_Constant(new operand::constant(pValue)),
		  _M_Category		 (category::constant)			{}
}