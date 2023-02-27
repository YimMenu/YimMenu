#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class seatbelt : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 32, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, true);
		}

		virtual void on_disable() override
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 32, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, false);
		}
	};

	seatbelt g_seatbelt("seatbelt", "Seatbelt", "Prevent you from falling off bikes or flying through the windshield",
	    g.vehicle.seatbelt);
}
