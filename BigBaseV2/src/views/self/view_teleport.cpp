#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/globals.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::teleport()
	{
		ImGui::Text("Blips:");

		components::button("Waypoint", []
		{
			teleport::to_waypoint();
		});

		components::button("Objective", []
		{
			teleport::to_objective();
		});

		ImGui::Text("Vehicles:");

		components::button("Teleport to Last Vehicle", []
		{
			if (g_local_player && g_local_player->m_vehicle)
			{
				const Vehicle veh = g_pointers->m_ptr_to_handle(g_local_player->m_vehicle);

				teleport::into_vehicle(veh);
			}
		});

		components::button("Bring Personal Vehicle", []
		{
			Vehicle veh = globals::get_personal_vehicle();

			vehicle::bring(veh, self::pos);
		});

		components::button("Teleport to Personal Vehicle", []
		{
			Vehicle veh = globals::get_personal_vehicle();

			teleport::into_vehicle(veh);
		});
	}
}
