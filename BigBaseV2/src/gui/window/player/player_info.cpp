#include "player_tabs.hpp"

namespace big
{
	void tab_player::tab_info()
	{
		if (ImGui::BeginTabItem("Info"))
		{
			ImGui::Checkbox("Spectate", &g.player.spectating);

			ImGui::EndTabItem();
		}
	}
}