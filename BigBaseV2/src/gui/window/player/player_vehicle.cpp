#include "player_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"
#include "features.hpp"

namespace big
{
	void tab_player::tab_vehicle()
	{
		if (ImGui::BeginTabItem("Vehicle"))
		{
			if (ImGui::Button("Teleport into Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id), false);

					teleport::into_vehicle(veh);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Clone Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id);
				Vehicle cloned = features::ClonePedVehicle(Handle);
				features::BoostStats(cloned);
				}QUEUE_JOB_END_CLAUSE


			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This will clone the peds vehicle and max it out");

			if (ImGui::Button("Kick out of car"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id);
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				}QUEUE_JOB_END_CLAUSE

			}
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("This will kick them from car by clearing task");

			ImGui::EndTabItem();
		}
	}
}