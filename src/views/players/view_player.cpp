#include "services/gui/gui_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::view_player()
	{
		ImGui::Checkbox("SPECTATE"_T.data(), &g.player.spectating);

		if (g_player_service->get_selected()->is_valid())
		{
			player_ptr current_player     = g_player_service->get_selected();
			navigation_struct& player_tab = g_gui_service->get_navigation().at(tabs::PLAYER);

			strcpy(player_tab.name, current_player->get_name());
			strcat(player_tab.name, std::format(" ({})", std::to_string(current_player->id())).data());

			if (current_player->is_host())
				strcat(player_tab.name, " [HOST]");

			if (current_player->is_friend())
				strcat(player_tab.name, " [FRIEND]");

			if (current_player->is_modder)
				strcat(player_tab.name, " [MOD]");

			view::player_info();
			ImGui::SameLine();
			view::player_teleport();

			view::player_kick();
			ImGui::SameLine();
			view::player_toxic();

			view::player_misc();
			ImGui::SameLine();
			view::player_vehicle();
		}
	}
}