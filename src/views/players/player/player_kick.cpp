#include "backend/commands/player/kick/bail_kick.hpp"
#include "backend/commands/player/kick/breakup_kick.hpp"
#include "backend/commands/player/kick/complaint_kick.hpp"
#include "backend/commands/player/kick/end_session_kick.hpp"
#include "backend/commands/player/kick/null_function_kick.hpp"
#include "backend/commands/player/kick/oom_kick.hpp"
#include "backend/commands/player/kick/script_host_kick.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_kick()
	{
		if (ImGui::TreeNode("KICK"_T.data()))
		{
			auto const is_session_host = [] {
				return gta_util::get_network()->m_game_session_ptr->is_host();
			};

			components::player_command_button(&cmd::g_breakup_kick, g_player_service->get_selected());
			ImGui::SameLine();
			components::command_checkbox(&cmd::g_show_cheating_message);

			components::player_command_button(&cmd::g_bail_kick, g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button(&cmd::g_null_function_kick, g_player_service->get_selected());

			components::player_command_button(&cmd::g_oom_kick, g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button(&cmd::g_script_host_kick, g_player_service->get_selected());

			components::player_command_button(&cmd::g_end_session_kick, g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button(&cmd::g_complaint_kick, g_player_service->get_selected());

			ImGui::TreePop();
		}
	}
}
