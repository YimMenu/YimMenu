#include "gui/tab_bar.hpp"
#include "features/functions.hpp"
#include "features/stats.hpp"
#include "natives.hpp"

namespace big
{
	void tabbar::render_misc()
	{
		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Text("Set Current Character Level:");
			ImGui::SliderInt("##input_levels_self", &g_temp.set_level, 0, 8000);
			if (ImGui::Button("Set Level"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					func::set_player_level(g_temp.set_level);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock Achievements"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					stats::unlock_achievements();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Max Character Stats"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int character_index;
					func::get_active_character_slot(&character_index);

					stats::max_stats(character_index);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Unlock All Stats"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					stats::unlock_all();
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}