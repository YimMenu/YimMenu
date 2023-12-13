#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class seatbelt : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 32, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, (int)eKnockOffVehicle::KNOCKOFFVEHICLE_NEVER);
		}

		virtual void on_disable() override
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 32, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, (int)eKnockOffVehicle::KNOCKOFFVEHICLE_DEFAULT);
		}
	};

	seatbelt g_seatbelt("seatbelt", "SEATBELT", "SEATBELT_DESC",
	    g.vehicle.seatbelt);
}
