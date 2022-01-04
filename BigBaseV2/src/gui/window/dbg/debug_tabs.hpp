#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	namespace modal_debug
	{
		void modal_new_global();
	}

	namespace tab_debug
	{
		void tab_globals();
		void tab_script_events();
		void _tab_debug();
	}
}