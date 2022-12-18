#include "gui/components/components.hpp"
#include "services/players/player_service.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::logs()
	{
		if (ImGui::BeginTabItem("Logs"))
		{
			ImGui::Checkbox("Log Metrics", &g.debug.logs.metric_logs);

			ImGui::Checkbox("Native Script Hooks", &g.debug.logs.script_hook_logs);

			if (ImGui::TreeNode("Script Event Logging"))
			{
				ImGui::Checkbox("Enable Script Event Logging", &g.debug.logs.script_event.logs);
				ImGui::Separator();

				ImGui::Checkbox("Filter by Player", &g.debug.logs.script_event.filter_player);

				if (g.debug.logs.script_event.filter_player)
				{
					ImGui::ListBoxHeader("##filter_player");
					for (const auto& [_, player] : g_player_service->players())
					{
						if (components::selectable(player->get_name(), g.debug.logs.script_event.player_id == player->id()))
						{
							g.debug.logs.script_event.player_id = player->id();
						}
					}
					ImGui::EndListBox();
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}