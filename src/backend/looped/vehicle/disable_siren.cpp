#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class siren_mute : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			Vehicle vehicle = self::veh;
			bool toggle     = true; // Enable muted siren state

			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
				{
					VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(vehicle, toggle);
				}
		}

		virtual void on_disable() override
		{
			Vehicle vehicle = self::veh;
			bool toggle     = false; // Enable muted siren state

			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
				{
					VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(vehicle, toggle);
				}
		}
	};

	siren_mute g_siren_mute("mutesiren", "Disable Siren", "Disables the siren sound of Emergency vehicles.",
	    g.vehicle.siren_mute);
}