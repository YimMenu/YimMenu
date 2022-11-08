#include "backend/looped/looped.hpp"

namespace big
{
	static bool bLastVehicleNoWaterCollsion = false;

	void looped::vehicle_no_water_collision()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr) return;

		bool bNoWaterCollsion = g->vehicle.no_water_collision;

		if (bNoWaterCollsion)
		{
			g_local_player->m_vehicle->m_navigation->m_damp->m_water_collision = 0;
			bLastVehicleNoWaterCollsion = bNoWaterCollsion;
		}
		else if (bNoWaterCollsion != bLastVehicleNoWaterCollsion)
		{
			g_local_player->m_vehicle->m_navigation->m_damp->m_water_collision = 1;
			bLastVehicleNoWaterCollsion = bNoWaterCollsion;
		}
	}
}