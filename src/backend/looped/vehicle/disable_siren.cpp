#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
    void looped::vehicle_disable_siren()
    {
		if (g.vehicle.enable_siren_mute = true)
		{
			Vehicle vehicle = self::veh;
			bool toggle     = true; // Enable muted siren state

			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
			{
				VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(vehicle, toggle);
			}
		}
    }
}