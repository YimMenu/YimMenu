#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/kick.hpp"

namespace big
{
	static bool bLastKickHost = false;
	void looped::session_auto_kick_host()
	{
		bool kick_host = *g_pointers->m_is_session_started && g->session.force_session_host && g->session.kick_host_when_forcing_host;
		if (kick_host && !bLastKickHost)
		{
			g_player_service->iterate([](auto& plyr)
			{
				if (plyr.second->is_host())
					kick::lost_connection_kick(plyr.second);
			});
		}
		bLastKickHost = kick_host;
	}
}
