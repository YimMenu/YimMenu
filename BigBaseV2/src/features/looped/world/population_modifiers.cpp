#include "features/world.hpp"
#include "natives.hpp"

namespace big
{
	void world::population_modifiers()
	{
		auto& population = g_settings.options["world"]["population"];

		if (population["enabled"])
		{
			PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME((float)population["pedestrians"].get<double>());

			VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME((float)population["parked"].get<double>());
			VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME((float)population["vehicles"].get<double>());
		}
	}
}