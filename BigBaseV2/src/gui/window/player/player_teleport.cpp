#include "player_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
	void tab_player::tab_teleport()
	{
		if (ImGui::BeginTabItem("Teleport"))
		{
			if (ImGui::Button("Teleport"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::to_player(g_player_service->get_selected()->id());
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::SameLine();
			if (ImGui::Button("Bring"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::bring_player(g_player_service->get_selected()->id());
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Godmode kill"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::godmode_kill(g_player_service->get_selected()->id());
				}QUEUE_JOB_END_CLAUSE
			}


			ImGui::EndTabItem();
		}
	}
}