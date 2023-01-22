#pragma once
#include "common.hpp"

namespace big
{
	class backend
	{
	public:
		static void loop();
		static void self_loop();
		static void weapons_loop();
		static void vehicles_loop();
		static void turnsignal_loop();
		static void misc_loop();
		static void remote_loop();
		static void lscustoms_loop();
		static void rainbowpaint_loop();
		static void vehiclefly_loop();
		static void disable_control_action_loop();
		static void world_loop();
	};
}
