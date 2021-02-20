#include "features/vehicle.hpp"
#include "gta_util.hpp"
#include "natives.hpp"

namespace big
{
	//static Vehicle veh = -1;

	void vehicle::handling()
	{
		if (g_local_ped == nullptr) return;

		g_temp.in_vehicle = g_local_ped->m_in_vehicle == 0;

		if (g_temp.in_vehicle)
			g_vehicle = g_local_ped->m_vehicle;
		else
			g_vehicle = nullptr;
	}
}