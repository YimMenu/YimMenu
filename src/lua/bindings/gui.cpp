#include "gui.hpp"

#include "../../gui.hpp"


namespace lua::gui
{
	bool is_open()
	{
		return big::g_gui->is_open();
	}
}