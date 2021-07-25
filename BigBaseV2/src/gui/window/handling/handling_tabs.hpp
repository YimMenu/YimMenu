#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	class tab_handling
	{
	public:
		static void tab_braking();
		static void tab_phyics();
		static void tab_suspension();
		static void tab_steering();
		static void tab_traction();
		static void tab_transmission();
	};
}