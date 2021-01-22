#pragma once
#include "imgui.h"

namespace big
{
	class window
	{
	public:
		static void render_top_bar();
		static void render_main_window();
		static void render_user_sidebar();
		static void render_player_window();

		static void render_handling_window();
	};
}