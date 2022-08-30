#include "views/view.hpp"
#include "gui.hpp"

namespace big
{
	void view::root()
	{
		if (g->window.main) 
			view::main_view();

		if (g->window.player)
			view::view_player();

		if (g->window.users)
			view::players();

		view::menu_bar();
		view::score_controller();
	}
}
