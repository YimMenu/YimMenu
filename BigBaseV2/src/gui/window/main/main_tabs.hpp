#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	class tab_main {
	public:
		static void tab_tunables();
		static void tab_self();
		static void tab_recovery();
		static void tab_settings();
		static void tab_spawn();
		static void tab_vehicle();
		static void tab_weapons();
		static void tab_teleport();
	};
}