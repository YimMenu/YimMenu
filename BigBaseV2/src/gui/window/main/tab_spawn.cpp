#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "core/data/vehicle_ids.hpp"

namespace big
{
	static char model[12];

	void tab_main::tab_spawn()
	{
		if (ImGui::BeginTabItem("Spawn"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			}QUEUE_JOB_END_CLAUSE

				if (
					ImGui::InputText("Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue) ||
					ImGui::Button("Spawn")
					)
				{
					QUEUE_JOB_BEGIN_CLAUSE(= )
					{
						Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
						Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

						vehicle::spawn((const char*)model, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
					}QUEUE_JOB_END_CLAUSE
				}

			vehicle_and_id selected{
				"bus",
				"bus"
			};
			if (ImGui::BeginCombo("Vehicles", selected.name)) {
				for (const vehicle_and_id& vehicle : vehicle_ids) {
					if (ImGui::Selectable(vehicle.name, vehicle.id == selected.id)) {
						strcpy(g.spawn.vehicle_id, vehicle.id);
					}
					if (vehicle.id == selected.id) {
						ImGui::SetItemDefaultFocus();
					}
				}
				if (ImGui::Button("Spawn")) {
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
						Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

						vehicle::spawn(g.spawn.vehicle_id, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
					}QUEUE_JOB_END_CLAUSE
				}
			}
			ImGui::EndCombo();
			ImGui::EndTabItem();
		}
	}
}
