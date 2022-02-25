#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::teleport() {

		ImGui::Text("Blips:");

		components::button("Waypoint", [] {
			teleport::to_waypoint();
			});

		components::button("Objective", [] {
			static const int blips[] = { 1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288 };
			for (int i = 0; i < (sizeof(blips) / sizeof(*blips)); i++) {
				if (teleport::to_blip(blips[i], 5)) {
					break;
				}

			}
			});

		ImGui::Text("Vehicles:");

		components::button("Bring Personal Vehicle", [] {
			Vehicle veh = globals::get_personal_vehicle();
			if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

			Vector3 location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

			vehicle::bring(veh, location);
			});

		components::button("Teleport to Personal Vehicle", [] {
			Vehicle veh = globals::get_personal_vehicle();
			if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

			teleport::to_coords(
				ENTITY::GET_ENTITY_COORDS(veh, true)
			);
			});
	}
}