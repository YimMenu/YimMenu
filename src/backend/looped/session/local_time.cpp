#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool toggled = true;

	void looped::session_local_time()
	{
		if (g.session.override_time)
		{
			if (toggled)
			{
				NETWORK::NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(&g.session.custom_time.hour,
				    &g.session.custom_time.minute,
				    &g.session.custom_time.second);
				toggled = false;
			}

			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g.session.custom_time.hour,
			    g.session.custom_time.minute,
			    g.session.custom_time.second);
		}
		else
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
			toggled = true;
		}
	}
}
