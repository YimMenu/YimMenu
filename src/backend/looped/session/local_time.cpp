#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::session_local_time()
	{
		if (g.world.custom_time.override_time)
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g.world.custom_time.hour,
			    g.world.custom_time.minute,
			    g.world.custom_time.second);
		}
		else
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	}
}
