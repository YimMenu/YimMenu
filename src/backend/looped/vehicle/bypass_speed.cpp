#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class bypass_speed : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			
			ENTITY::SET_ENTITY_MAX_SPEED(self::veh, FLT_MAX);
		}
		
		

		virtual void on_disable() override
		{
			ENTITY::SET_ENTITY_MAX_SPEED(self::veh, 150);
		}
	};

	bypass_speed g_bypass_speed("nospeedlimit", "BYPASS_SPEED", "BYPASS_SPEED_DESC", g.vehicle.bypass_speed);
}