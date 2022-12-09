#pragma once

namespace ampersand::poly::machine {
	struct format_category {	
		struct		  call		  {};
		struct		  call_method {};

		struct      create_object {};
		struct      delete_object {};
		struct   reference_object {};

		struct primitive_operator {};
		struct         move		  {};
		struct shallow_move		  {};
		struct	  deep_move		  {};
	};
}