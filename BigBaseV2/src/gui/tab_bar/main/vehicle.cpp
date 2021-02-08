#include "gui/tab_bar.hpp"
#include "features/notify.hpp"
#include "features/teleport.hpp"
#include "gta_util.hpp"

namespace big
{
	void tabbar::render_vehicle()
	{
		if (ImGui::BeginTabItem("Vehicle"))
		{
			bool bVehGodMode = g_vehicle == nullptr ? false : (g_vehicle->m_godmode & 0x1) == 0x1;
			if (ImGui::Checkbox("Vehicle God Mode", &bVehGodMode))
				if (g_vehicle != nullptr)
					g_vehicle->m_godmode = bVehGodMode ? 0x1 : 0x0;

			ImGui::Separator();

			if (ImGui::TreeNode("Speedometer"))
			{
				static const char* speedo_options[] = { "None", "km/h", "mph" };
				if (ImGui::BeginCombo("##speedometer", speedo_options[g_settings.options["speedo_type"].get<int64_t>()]))
				{
					for (uint8_t i = 0; i < IM_ARRAYSIZE(speedo_options); i++)
					{
						bool is_selected = (g_settings.options["speedo_type"].get<int64_t>() == i);
						if (ImGui::Selectable(speedo_options[i], is_selected))
						{
							*g_settings.options["speedo_type"].get<int64_t*>() = i;
							g_settings.save();
						}
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				ImGui::TreePop();
			}

			ImGui::Separator();

			ImGui::Checkbox("Handling", &g_temp.windows.handling);

			ImGui::Separator();

			if (ImGui::Button("Auto Pilot"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

					if (!veh)
						notify::above_map("~r~Make sure you are in a vehicle.");
					else if (!HUD::DOES_BLIP_EXIST(blipHandle))
						notify::above_map("~r~Waypoint needs to be set.");
					else
					{
						Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);
						// Make sure the AI can reach this
						if (teleport::load_ground_at_3dcoord(location))
							TASK::TASK_VEHICLE_DRIVE_TO_COORD(PLAYER::PLAYER_PED_ID(), veh, location.x, location.y, location.z, 35.f, 0, veh, 2883620, 10.f, true);
						else
							notify::above_map("Unable to find ground at location.");
					}
				}QUEUE_JOB_END_CLAUSE
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop Auto Pilot"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Ped player = PLAYER::PLAYER_PED_ID();

					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player, false);

					Vector3 location = ENTITY::GET_ENTITY_COORDS(player, true);

					TASK::TASK_VEHICLE_DRIVE_TO_COORD(player, veh, location.x, location.y, location.z, 35.f, 0, veh, 2883620, 10.f, true);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::Separator();

			ImGui::Checkbox("No Bike Fall", g_settings.options["no_bike_fall"].get<bool*>());

			ImGui::Checkbox("Sticky Tyres", g_settings.options["sticky_tyres"].get<bool*>());

			if (ImGui::Button("Repair Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_FIXED(veh);

						notify::above_map("Vehicle has been repaired.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Clean Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), false);

					if (veh)
					{
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.0);

						notify::above_map("Vehicle has been cleaned.");
					}
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Bullet Proof Tyres"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), false);

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