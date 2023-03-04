#include "backend/looped/looped.hpp"
#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	static bool bLastKickHost = false;
	void looped::session_auto_kick_host()
	{
		bool kick_host = *g_pointers->m_is_session_started && g.session.force_session_host && g.session.kick_host_when_forcing_host;
		if (kick_host && !bLastKickHost)
		{
			g_player_service->iterate([](auto& plyr) {
				if (plyr.second->is_host())
				{
					((player_command*)(command::get(RAGE_JOAAT("lckick"))))->call(plyr.second, {});
				}
			});
		}
		bLastKickHost = kick_host;
	}
}
