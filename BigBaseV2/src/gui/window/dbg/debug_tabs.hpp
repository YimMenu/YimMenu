#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	struct modal_debug
	{
		static void modal_new_global();
	};

	struct tab_debug
	{
		static void tab_globals();
		static void tab_script_events();
		static void _tab_debug();
	};
}