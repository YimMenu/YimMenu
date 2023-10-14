#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	class time_override : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g.world.custom_time.hour,
			    g.world.custom_time.minute,
			    g.world.custom_time.second);
		}

		virtual void on_disable() override
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	};

	time_override g_time_override("timeoverride", "BACKEND_LOOPED_WORLD_OVERRIDE_TIME", "BACKEND_LOOPED_WORLD_OVERRIDE_TIME_DESC", g.world.custom_time.override_time);
}