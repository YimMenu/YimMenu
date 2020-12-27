#pragma once
#include "tab_bar.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big
{
	void tabbar::render_network()
	{
		if (ImGui::BeginTabItem("Network"))
		{
			if (ImGui::Checkbox("Reveal Players", g_settings.options["reveal_players"].get<bool*>()))
				g_settings.save();

			ImGui::Separator();

			ImGui::Text("Time: ");
			ImGui::SliderInt("Hour:", &g_temp.time.hour, 0, 23);
			ImGui::SliderInt("Minutes:", &g_temp.time.minutes, 0, 59);
			if (ImGui::Button("Apply"))
			{
				QUEUE_JOB_BEGIN_CLAUSE(= )
				{
					NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_temp.time.hour, g_temp.time.minutes, 0);

					g_pointers->m_sync_local_time(1, 0);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			if (ImGui::Checkbox("Spoof Online Rank", g_settings.options["spoof_rank"].get<bool*>()))
				g_settings.save();

			if (ImGui::InputInt(": Rank", (PINT)g_settings.options["rank"].get<int64_t*>(), 1, 50))
				g_settings.save();

			ImGui::EndTabItem();
		}
	}
}