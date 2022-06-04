#include "views/view.hpp"
#include "gui.hpp"

namespace big
{
	void view::root()
	{
		if (g->window.main) 
		{
			view::navigation();
			view::players();
			view::active_view();
		}
		view::debug_c();
		view::menu_bar();
	}
}
