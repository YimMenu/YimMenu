#include "gui/tab_bar.hpp"
#include "pointers.hpp"

namespace big
{
	static char model[12];

	void tabbar::render_spawn()
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
					Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);
					Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

					func::spawn_vehicle((const char*)model, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}