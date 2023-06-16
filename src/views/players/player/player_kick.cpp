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

			if (!g_player_service->get_self()->is_host())
				ImGui::Text("These kicks require host"), ImGui::BeginDisabled();
			
			components::button("Host kick", []{NETWORK::NETWORK_SESSION_KICK_PLAYER(g_player_service->get_selected()->id());}),
			components::player_command_button<"breakup">(g_player_service->get_selected());

			ImGui::EndDisabled();

			ImGui::SameLine();
			components::command_checkbox<"breakupcheating">();

			components::player_command_button<"bailkick">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"nfkick">(g_player_service->get_selected());

			components::player_command_button<"oomkick">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"shkick">(g_player_service->get_selected());

			components::player_command_button<"endkick">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"desync">(g_player_service->get_selected());

			ImGui::TreePop();
		}
	}
}