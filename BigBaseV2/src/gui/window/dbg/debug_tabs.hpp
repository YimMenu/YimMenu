#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
<<<<<<<<< Temporary merge branch 1
	struct modal_debug
	{
		void modal_new_global();
	}

	namespace tab_debug
	{
=========
	class tab_debug {
	public:
>>>>>>>>> Temporary merge branch 2
		static void tab_globals();
		static void tab_script_events();
		static void _tab_debug();
	};
}