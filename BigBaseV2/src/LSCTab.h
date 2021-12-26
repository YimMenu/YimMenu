#pragma once
#include "common.hpp"
#include "imgui.h"
#include "natives.hpp"
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
}