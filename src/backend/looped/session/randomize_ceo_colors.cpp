#include "backend/looped/looped.hpp"
#include "gta/script_handler.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/session.hpp"

namespace big
{
	void looped::session_randomize_ceo_colors()
	{
		if (g.session.randomize_ceo_colors && *g_pointers->m_gta.m_is_session_started && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) == 0)
		{
			if (auto freemode = gta_util::find_script_thread("freemode"_J);
			    freemode && freemode->m_net_component && ((CGameScriptHandlerNetComponent*)freemode->m_net_component)->is_local_player_host())
			{
				for (int i = 0; i < *scr_globals::gsbd.at(818).at(44).as<int*>(); i++)
				{
					*scr_globals::gsbd.at(818).at(44).at(i, 2).at(1).as<int*>() = rand() % 15;
				}
			}
		}
	}
}
