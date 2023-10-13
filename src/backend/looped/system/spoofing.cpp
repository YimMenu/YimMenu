#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "core/settings/session.hpp"
#include "gta_util.hpp"
#include "natives.hpp"

#include <network/CCommunications.hpp>
#include <network/Network.hpp>
#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	static bool bLastForceHost = false;
	void looped::system_spoofing()
	{
		if (bLastForceHost != g_session.force_session_host && gta_util::get_network()->m_game_session_state == 0)
		{
			uint64_t host_token;
			g_pointers->m_gta.m_generate_uuid(&host_token);

			host_token = g_session.force_session_host ? (rand() % 10000) : host_token;

			*g_pointers->m_gta.m_host_token = host_token;

			if (gta_util::get_network()->m_game_session_ptr)
				gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token = host_token;

			g_pointers->m_gta.m_profile_gamer_info->m_host_token                                       = host_token;
			g_pointers->m_gta.m_player_info_gamer_info->m_host_token                                   = host_token;
			(*g_pointers->m_gta.m_communications)->m_voice.m_connections[0]->m_gamer_info.m_host_token = host_token;

			if (g_local_player && g_local_player->m_player_info)
				g_local_player->m_player_info->m_net_player_data.m_host_token = host_token;

			bLastForceHost = g_session.force_session_host;
		}
	}
}
