#include "views/view.hpp"
#include "gui.hpp"

namespace big
{
	void view::root()
	{
		if (g->window.main) 
			view::main_view();

		if (g->window.player)
			view::view_player_tabs();

		if (g->window.users)
			view::players();

		if (g->window.demo)
			ImGui::ShowDemoWindow(&g->window.demo);

		view::menu_bar();
		view::score_controller();
	}
}
