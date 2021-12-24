#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	class tab_debug {
	public:
		static void tab_globals();
		static void tab_script_events();
		static void _tab_debug();
	};
}