#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
	void tab_main::tab_teleport()
	{
		if (ImGui::BeginTabItem("Teleport"))
		{
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
					static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
					for (int i = 0; i < (sizeof(blips) / sizeof(*blips)); i++) {
						if (teleport::to_blip(blips[i], 5)) {
							break;
						}

					}
				}QUEUE_JOB_END_CLAUSE
			}

			static int selected_seat = 0;
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

			ImGui::EndTabItem();
		}
	}
}