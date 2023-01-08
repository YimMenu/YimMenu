#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class vehinvisibility : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::veh, false, 0);
			if (g.vehicle.localveh_visibility)
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::veh);
			if (g.vehicle.localped_visibility && g.vehicle.vehinvisibility)
				ENTITY::SET_ENTITY_VISIBLE(self::ped, true, 0);
		}

		virtual void on_disable() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::veh, true, 0);
		}
	};

	vehinvisibility g_vehinvisibility("invisveh", "Vehicle Invisiblity", "Makes your car invisible", g.vehicle.vehinvisibility);
	bool_command g_localveh_visibility("localinvisveh", "Visible Locally", "Makes your car visible to yourself, other players will still not be able to see it", g.vehicle.localveh_visibility);
	bool_command g_localped_visibility("localinvisped", "Self Visible", "Makes yourself visible driving the vehicle to others and yourself,\n car will still be invisible but you can be", g.vehicle.localped_visibility);
}
