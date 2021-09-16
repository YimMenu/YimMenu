#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	class tab_handling
	{
	public:
		static void tab_brakes();
		static void tab_gearing();
		static void tab_general();
		static void tab_other();
		static void tab_rollbars();
		static void tab_roll_centre_height();
		static void tab_suspension();
		static void tab_steering();
		static void tab_traction();
		static void tab_transmission();
	};

	class modal_handling
	{
	public:
		static void modal_save_handling();
	};
}