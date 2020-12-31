#include "features.hpp"

namespace big
{
	void features::population_modifiers()
	{
		if (g_settings.options["population_modifiers"].get<bool>())
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME((float)g_settings.options["pedestrian_population"].get<double>());
			
				VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME((float)g_settings.options["parked_vehicle_density"].get<double>());
				VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME((float)g_settings.options["vehicle_density"].get<double>());
			}QUEUE_JOB_END_CLAUSE
		}
	}
}