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
			teleport::to_objective();
			});

		ImGui::Text("Vehicles:");

		components::button("Bring Personal Vehicle", [] {
			Vehicle veh = globals::get_personal_vehicle();
			if (ENTITY::IS_ENTITY_DEAD(veh, false)) return g_notification_service->push_error("Teleport", "Invalid vehicle handle...");

			vehicle::bring(veh, self::pos);
			});

		components::button("Teleport to Personal Vehicle", [] {
			Vehicle veh = globals::get_personal_vehicle();
			if (ENTITY::IS_ENTITY_DEAD(veh, false)) return g_notification_service->push_error("Teleport", "Invalid vehicle handle...");

			teleport::to_coords(
				ENTITY::GET_ENTITY_COORDS(veh, true)
			);
			});
	}
}