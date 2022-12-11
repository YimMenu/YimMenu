#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/kick.hpp"

namespace big
{
	void view::player_kick()
	{
		if (ImGui::TreeNode("Kick"))
		{
			components::button("Breakup Kick", [] { kick::breakup_kick(g_player_service->get_selected()); });
			components::button("Lost Connection Kick", [] { kick::lost_connection_kick(g_player_service->get_selected()); });
			components::button("Bail Kick", [] { kick::bail_kick(g_player_service->get_selected()); });
			components::button("Null Function Kick", [] { kick::null_function_kick(g_player_service->get_selected()); });
			components::button("OOM Kick", [] { kick::oom_kick(g_player_service->get_selected()); });
			components::button("Script Host Kick", [] { kick::kick_player_script_host(g_player_service->get_selected()); });
			components::button("End Session Kick", [] { kick::end_session_kick(g_player_service->get_selected()); });
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("The kick can take around 10 seconds to work");
			components::button("Host Kick", [] { kick::host_kick(g_player_service->get_selected()); });
			components::button("Complaint Kick", [] { kick::complaint_kick(g_player_service->get_selected()); });
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("The kick can take around 10 seconds to work");

			ImGui::TreePop();
		}
	}
}