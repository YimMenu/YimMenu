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

			if (ImGui::Button("Delete Vehicle"))
			{
				g_fiber_pool->queue_job([]
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(g.selected_player.id, false));

						while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(g.selected_player.id, false)))
							script::get_current()->yield(5ms);
						Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(g.selected_player.id);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, true, true);
						VEHICLE::DELETE_VEHICLE(&veh);
					});
			}

			if (ImGui::Button("Gift vehicle"))
			{
				g_fiber_pool->queue_job([]
					{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehicle);

				while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle))
					script::get_current()->yield(10ms);

				DECORATOR::DECOR_REGISTER("PV_Slot", 3);
				DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
				DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
				DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(g.selected_player.id));
				VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
				notify::above_map("Vehicle Gifted");
					});
			}

			ImGui::EndTabItem();
		}
	}
}