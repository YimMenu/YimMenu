#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "persist/PersistTeleport.h"

namespace big
{
	void tab_main::tab_teleport()
	{
		if (ImGui::BeginTabItem("Teleport"))
		{
			ImGui::BeginChild("col1", { 200.f, 0.f });

			ImGui::Text("Blips:");

			if (ImGui::Button("Waypoint"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					teleport::to_waypoint();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Objective"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					for (int i = 0; i <= 1000; i++)
					{
						Blip_t* blip = g_pointers->pBlipList->m_Blips[i].m_pBlip;
						if (blip)
						{
							if ((blip->m_color == BlipColors::Mission && blip->m_icon == Circle) ||
								(blip->m_color == BlipColors::YellowMission && blip->m_icon == Circle) ||
								(blip->m_color == BlipColors::YellowMission2 && (blip->m_icon == Circle || blip->m_icon == BlipIcons::DollarSign)) ||
								(blip->m_color == BlipColors::None && blip->m_icon == BlipIcons::RaceFlagWithArrow) ||
								(blip->m_color == BlipColors::Green && blip->m_icon == Circle) ||
								(blip->m_icon == BlipIcons::Crate))
							{
								PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), blip->x, blip->y, blip->z);
								break; //During a race there's sometimes 2 yellow markers. We want the first one.
							}
						}
					}
				}QUEUE_JOB_END_CLAUSE
			}

			
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("col2", { 0.f, 0.f });

			ImGui::Text("Vehicles:");
			if (ImGui::Button("Bring Personal Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vehicle veh = globals::get_personal_vehicle();
					if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

					Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

					vehicle::bring(veh, location);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Teleport to Personal Vehicle"))
			{
				Vehicle veh = globals::get_personal_vehicle();
				if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

				teleport::to_coords(
					ENTITY::GET_ENTITY_COORDS(veh, true)
				);
			}
			ImGui::EndChild();
			static int selected_seat;
			const char* const vehicle_seats[]
			{
				"Passenger ",
				"Left Rear",
				"RightRear",
			};

			ImGui::Combo("##vehicle_seat", &selected_seat, vehicle_seats, IM_ARRAYSIZE(vehicle_seats));

			ImGui::SameLine();

			if (ImGui::Button("teleport to nearest vehicle"))
			{
				g_fiber_pool->queue_job([]
					{
						LOG(INFO) << selected_seat;
						auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), VEHICLE::GET_CLOSEST_VEHICLE(pos.x, pos.y, pos.z, 1000, 0, 70), selected_seat);
					});
			}

			persist_teleport::do_presentation_layer();
			ImGui::EndTabItem();
		}
	}
}