#include "backend/commands/player/troll/bring.hpp"
#include "backend/commands/player/troll/remote_control_vehicle.hpp"
#include "backend/commands/player/troll/set_bounty.hpp"
#include "backend/commands/player/troll/teleport.hpp"
#include "backend/commands/player/troll/teleport_into_vehicle.hpp"
#include "util/teleport.hpp"
#include "util/troll.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_troll()
	{
		if (ImGui::TreeNode("TROLL"_T.data()))
		{
			components::player_command_button(&cmd::g_teleport_to_player, g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button(&cmd::g_bring, g_player_service->get_selected());

			components::player_command_button(&cmd::g_teleport_into_vehicle, g_player_service->get_selected());
			components::player_command_button(&cmd::g_remote_control_vehicle, g_player_service->get_selected());

			static int bounty_value = 0;

			ImGui::SliderInt("BOUNTY"_T.data(), &bounty_value, 0, 10000);
			ImGui::SameLine();
			components::command_checkbox(&cmd::g_anonymous_bounty);
			ImGui::SameLine();
			components::button("SET"_T, [] {
				troll::set_bounty_on_player(g_player_service->get_selected(), bounty_value, g.session.anonymous_bounty);
			});

			ImGui::TreePop();
		}
	}
}
