#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::session_local_time()
	{
		if (g.session.override_time)
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g.session.custom_time.hour,
			    g.session.custom_time.minute,
			    g.session.custom_time.second);
		}
		else
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	}
}
