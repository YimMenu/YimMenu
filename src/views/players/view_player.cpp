#include "views/view.hpp"

namespace big
{
	void view::view_player()
	{
		ImGui::Text("VIEW_PLAYER_PLAYER_OPTIONS"_T.data(), g_player_service->get_selected()->get_name());
		ImGui::Checkbox("SPECTATE"_T.data(), &g.player.spectating);

		if (g_player_service->get_selected()->is_valid())
		{
			view::player_info();
			view::player_troll();
			view::player_kick();
			view::player_toxic();
			view::player_misc();
			view::player_vehicle();
			view::player_attacker();
		}
	}
}