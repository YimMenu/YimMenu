#pragma once
#include "common.hpp"
#include "imgui.h"

namespace big
{
	class lsc_tab
	{
	public:
		static void render_lsc_tab();
	private:
		static const char* get_mod_slot_name(int mod_slot, Vehicle vehicle);
		static const char* get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle);
	};
	class tab_main {
	public:
		static void tab_tunables();
		static void tab_self();
		static void tab_recovery();
		static void tab_settings();
		static void tab_spawn();
		static void tab_spoofing();
		static void tab_vehicle();
		static void tab_weapons();
		static void tab_teleport();
	};
}