#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class keep_on_ground : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(self::veh, 5.0);
		}
	};

	keep_on_ground g_keep_on_ground("keeponground", "Keep On Ground", "Makes it so your vehicle is always on the ground on all four wheels", g.vehicle.keep_on_ground);
}