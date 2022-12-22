#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"

namespace big
{
	void view::player_kick()
	{
		if (ImGui::TreeNode("Kick"))
		{
			components::player_command_button<"breakup">(g_player_service->get_selected());
			components::player_command_button<"lckick">(g_player_service->get_selected());
			components::player_command_button<"bailkick">(g_player_service->get_selected());
			components::player_command_button<"nfkick">(g_player_service->get_selected());
			components::player_command_button<"oomkick">(g_player_service->get_selected());
			components::player_command_button<"shkick">(g_player_service->get_selected());
			components::player_command_button<"endkick">(g_player_service->get_selected());
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("The kick can take around 10 seconds to work");
			components::player_command_button<"hostkick">(g_player_service->get_selected());
			components::player_command_button<"desync">(g_player_service->get_selected());
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("The kick can take around 10 seconds to work");

			ImGui::TreePop();
		}
	}
}