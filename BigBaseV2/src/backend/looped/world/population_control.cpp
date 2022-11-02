#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::world_population_control()
	{
		if (g->session.population_control.ped_enable)
		{
            STREAMING::SET_PED_POPULATION_BUDGET(g->session.population_control.ped);
        }
        if (g->session.population_control.vehicle_enable)
		{
            STREAMING::SET_VEHICLE_POPULATION_BUDGET(g->session.population_control.vehicle);
        }
	}
}
 
