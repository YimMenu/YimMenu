#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class bypass_speed : looped_command
	{
		using looped_command::looped_command;

	Vehicle stored_veh = 0;
		float stored_speed = 0;
		virtual void on_init()
		{
			Vehicle stored_veh = self::veh;
			float stored_speed = VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(self::veh);
		}

		virtual void on_tick()
		{
			if (stored_veh != self::veh)
			{
				ENTITY::SET_ENTITY_MAX_SPEED(stored_veh, stored_speed);
				stored_veh = self::veh;
			}
			else
				ENTITY::SET_ENTITY_MAX_SPEED(self::veh, FLT_MAX);
		}

		virtual void on_disable()
		{
			ENTITY::SET_ENTITY_MAX_SPEED(self::veh, stored_speed);
		}
	};

	bypass_speed g_bypass_speed("nospeedlimit", "BYPASS_SPEED", "BYPASS_SPEED_DESC", g.vehicle.bypass_speed);
}