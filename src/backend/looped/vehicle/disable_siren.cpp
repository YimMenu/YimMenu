#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class siren_mute : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (ENTITY::DOES_ENTITY_EXIST(self::veh))
			{
				VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(self::veh, true); // Enables muted siren state
			}
		}

		virtual void on_disable() override
		{
			if (ENTITY::DOES_ENTITY_EXIST(self::veh))
			{
				VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(self::veh, false); // Disables muted siren state
			}
		}
	};

	siren_mute g_siren_mute("mutesiren", "MUTE_SIREN", "MUTE_SIREN_DESC",
	    g.vehicle.siren_mute);
}
