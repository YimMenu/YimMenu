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
					teleport::to_player(g_player_service->m_selected_player->id());
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::SameLine();
			if (ImGui::Button("Bring"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::bring_player(g_player_service->m_selected_player->id());
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Teleport into Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->m_selected_player->id()), false);
					
					teleport::into_vehicle(veh);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}