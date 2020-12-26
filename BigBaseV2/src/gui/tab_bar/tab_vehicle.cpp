#pragma once
#include "tab_bar.hpp"

namespace big
{
	void tabbar::render_vehicle()
	{
		if (ImGui::BeginTabItem("Vehicle"))
		{
			ImGui::Checkbox("No Bike Fall", g_settings.options["no_bike_fall"].get<bool*>());

			ImGui::Checkbox("Sticky Tyres", g_settings.options["sticky_tyres"].get<bool*>());

			if (ImGui::Button("Repair Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_FIXED(veh);

						features::notify::above_map("Vehicle has been repaired.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Clean Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.0);

						features::notify::above_map("Vehicle has been cleaned.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Bullet Proof Tyres"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
					}
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}