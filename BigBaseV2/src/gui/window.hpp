#pragma once
#include "natives.hpp"

namespace big
{
	class window {
		static void debug();
		static void top_bar();
		static void handling();
		static void log();
		static void main();
		static void w_player();
		static void users();

	public:
		static void draw_all()
		{
			window::top_bar();

			window::log();

			window::debug();

			window::main();
			window::handling();

			window::w_player();
			window::users();
		}
	};
}