#include "fiber_pool.hpp"
#include "main_tabs.hpp"
#include "script.hpp"
#include "util/player.hpp"

namespace big
{
	void tab_main::tab_recovery()
	{
		if (ImGui::BeginTabItem("Recovery"))
		{
			ImGui::Text("Set Current Character Level:");
			ImGui::SliderInt("##input_levels_self", &g->player.set_level, 0, 8000);
			if (ImGui::Button("Set Level"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					player::set_player_level(g->player.set_level);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}