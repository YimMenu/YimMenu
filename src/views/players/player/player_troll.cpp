#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "util/troll.hpp"

namespace big
{
	void view::player_troll()
	{
		if (ImGui::TreeNode("Troll"))
		{
			components::player_command_button<"playertp">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"bring">(g_player_service->get_selected());

			components::player_command_button<"playervehtp">(g_player_service->get_selected());
			components::player_command_button<"rcplayer">(g_player_service->get_selected());

			static int bounty_value = 0;
			
			ImGui::SliderInt("Bounty", &bounty_value, 0, 10000);
			ImGui::SameLine();
			components::command_checkbox<"anonbounty">();
			ImGui::SameLine();
			components::button("Set", [] { troll::set_bounty_on_player(g_player_service->get_selected(), bounty_value, g.session.anonymous_bounty);});

			ImGui::TreePop();
		}
	}
}
