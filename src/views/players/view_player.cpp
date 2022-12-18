#include "views/view.hpp"

namespace big
{
	void view::view_player() {

		std::string title = std::format("Player Options: {}", g_player_service->get_selected()->get_name());
		
		ImGui::Text(title.c_str());
		ImGui::Checkbox("Spectate", &g.player.spectating);
		
		if (g_player_service->get_selected()->is_valid())
		{
			view::player_info();
			view::player_troll();
			view::player_kick();
			view::player_toxic();
			view::player_misc();
		}
	}
}