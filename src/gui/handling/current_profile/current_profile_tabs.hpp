#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	namespace tab_current_profile
	{
		void tab_brakes();
		void tab_gearing();
		void tab_general();
		void tab_other();
		void tab_rollbars();
		void tab_roll_centre_height();
		void tab_suspension();
		void tab_steering();
		void tab_traction();
		void tab_transmission();
	}

	namespace modal_handling
	{
		void modal_save_handling();
	}
}