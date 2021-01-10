#include "tab_bar.hpp"
#include "features/rid_joiner.hpp"

namespace big
{
	void tabbar::render_misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			if (ImGui::Button("Join R* Id"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					g_rid_joiner.join_player(143069134);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Text("Set Current Character Level:");
			ImGui::SliderInt("##input_levels_self", &g_temp.set_level, 0, 8000);
			if (ImGui::Button("Set Level"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::functions::set_player_level(g_temp.set_level);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock Achievements"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::stats::unlock_achievements();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock All Stats"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					features::stats::unlock_all();
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}