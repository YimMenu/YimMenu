#include "gui_main.hpp"
#include "window.hpp"

namespace big
{
	void main_gui::draw()
	{
		window::top_bar();

		window::log();

		window::debug();

		window::main();
		window::handling();

		window::player();
		window::users();
	}
}