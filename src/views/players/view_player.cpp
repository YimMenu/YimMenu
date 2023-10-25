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

			std::string name_appendage{};
			if (current_player->is_host())
			{
				name_appendage += std::format(" [{}]", "VIEW_PLAYER_IS_HOST"_T);
			}
			if (current_player->is_friend())
			{
				name_appendage += std::format(" [{}]", "VIEW_PLAYER_IS_FRIEND"_T);
			}
			if (current_player->is_modder)
			{
				name_appendage += std::format(" [{}]", "MOD"_T);
			}
			if (current_player->is_trusted)
			{
				name_appendage += std::format(" [{}]", "TRUST"_T);
			}
			strcpy(player_tab.name, std::format("{} ({}){}", current_player->get_name(), current_player->id(), name_appendage).c_str());

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