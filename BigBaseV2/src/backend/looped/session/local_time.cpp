#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool lastOverride = true;

	void looped::session_local_time()
	{
		if (lastOverride && !g->session.override_time)
		{
			NETWORK::NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(&g->session.custom_time.hour, &g->session.custom_time.minute, &g->session.custom_time.second);
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g->session.custom_time.hour, g->session.custom_time.minute, g->session.custom_time.second);
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
			lastOverride = false;
		}

		if (g->session.override_time)
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g->session.custom_time.hour, g->session.custom_time.minute, g->session.custom_time.second);
			lastOverride = true;
		}
	}
}