#pragma once
#include "common.hpp"
#include "imgui.h"
#include "features.hpp"
#include "settings.h"
#include "natives.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"

namespace big
{
	class tabbar
	{
	public:
		// Order in the order that they are rendered/sorted in the UI
		static void render_self();
		static void render_weapons();
		static void render_tunables();
		static void render_teleport();
		static void render_vehicle();
		static void render_world();
		static void render_online();
		static void render_misc();
		static void render_spawn();
		static void render_settings();

		static void player_info();
		static void player_griefing();
		static void player_teleport();
		static void player_drop();

		static void handling_physics();
		static void handling_transmission();
		static void handling_brakes();
		static void handling_traction();
		static void handling_suspension();
	};

}