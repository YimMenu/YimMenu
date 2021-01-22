#include "features.hpp"
#include "gta_util.hpp"

namespace big
{
	static Vehicle veh = -1;

	void features::handling()
	{
		CPed* ped = gta_util::get_local_ped();

		g_in_vehicle = ped->m_in_vehicle == 0;

		if (g_in_vehicle)
		{
			Vehicle currVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			if (veh != currVeh && ped->m_vehicle != NULL)
			{
				veh = currVeh;

				// Copy the new vehicle data to our global
				g_vehicle = ped->m_vehicle;
			}
		}
	}
}