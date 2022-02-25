#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"

namespace big
{
	static char model[12];

	void view::spawn() {
		g_fiber_pool->queue_job([] {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			});

		if (
			ImGui::InputText("Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue) ||
			ImGui::Button("Spawn")
			)
		{
			g_fiber_pool->queue_job([] {
				Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
				Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

				vehicle::spawn((const char*)model, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
				});
		}
	}
}