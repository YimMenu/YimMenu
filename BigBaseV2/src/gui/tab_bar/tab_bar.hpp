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
		static void render_tunables();
		static void render_teleport();
		static void render_vehicle();
		static void render_network();
		static void render_spawn();
	};

}