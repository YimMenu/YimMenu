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

		ImGui::EndTabItem();
	}
}