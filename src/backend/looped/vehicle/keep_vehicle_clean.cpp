#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class keep_vehicle_clean : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (ENTITY::DOES_ENTITY_EXIST(self::veh))
			{
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(self::veh, 0.0f);
			}
		}
	};

	keep_vehicle_clean
	    g_keep_vehicle_clean("keepvehicleclean", "KEEP_VEHICLE_CLEAN_CMD", "KEEP_VEHICLE_CLEAN_CMD_DESC", g.vehicle.keep_vehicle_clean);
}