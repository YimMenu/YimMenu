#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "script_global.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

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
					static const int blips[] = {1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288};
					for (int i = 0; i < (sizeof(blips)/sizeof(*blips)); i++) {
						if (teleport::to_blip(blips[i], 5)) {
							break;
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
					Vehicle veh = *script_global(2810287).at(298).as<Vehicle*>();
					if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

					Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

					vehicle::bring(veh, location);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Teleport to Personal Vehicle"))
			{
				Vehicle veh = *script_global(2810287).at(298).as<Vehicle*>();
				if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

				teleport::to_coords(
					ENTITY::GET_ENTITY_COORDS(veh, true)
				);
			}

			ImGui::EndChild();

			ImGui::EndTabItem();
		}
	}
}