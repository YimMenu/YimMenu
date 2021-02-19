#include "features/vehicle.hpp"
#include "gta_util.hpp"
#include "natives.hpp"

namespace big
{
	//static Vehicle veh = -1;

	void vehicle::handling()
	{
		CPed* ped = gta_util::get_local_ped();

		g_temp.in_vehicle = ped->m_in_vehicle == 0;

		if (g_temp.in_vehicle)
			g_vehicle = ped->m_vehicle;
		else
			g_vehicle = nullptr;
	}
}