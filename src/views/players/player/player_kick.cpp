#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"

namespace big
{
	void view::player_kick()
	{
		if (ImGui::TreeNode("Kick"))
		{
			components::player_command_button<"breakup">("Breakup Kick", g_player_service->get_selected(), { });
			components::player_command_button<"lckick">("Lost Connection Kick", g_player_service->get_selected(), { });
			components::player_command_button<"bailkick">("Bail Kick", g_player_service->get_selected(), { });
			components::player_command_button<"nfkick">("Null Function Kick", g_player_service->get_selected(), { });
			components::player_command_button<"oomkick">("OOM Kick", g_player_service->get_selected(), { });
			components::player_command_button<"shkick">("Script Host Kick", g_player_service->get_selected(), { });
			components::player_command_button<"endkick">("End Session Kick", g_player_service->get_selected(), { });
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("The kick can take around 10 seconds to work");
			components::player_command_button<"hostkick">("Host Kick", g_player_service->get_selected(), { });
			components::player_command_button<"desync">("Desync Kick", g_player_service->get_selected(), { });
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("The kick can take around 10 seconds to work");

			ImGui::TreePop();
		}
	}
}