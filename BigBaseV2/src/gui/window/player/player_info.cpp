#include "player_tabs.hpp"

namespace big
{
	void tab_player::tab_info()
	{
		if (ImGui::BeginTabItem("Info"))
		{
			ImGui::Checkbox("Spectate", &g.player.spectating);

			ImGui::Separator();

			ImGui::Text("Player ID: %d", g.selected_player.id);
			ImGui::Text("Session Host: %s", g.selected_player.net_player->is_host() ? "Yes" : "No");

			ImGui::EndTabItem();
		}
	}
}