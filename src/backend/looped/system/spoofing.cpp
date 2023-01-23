#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include <network/Network.hpp>
#include <network/CCommunications.hpp>

namespace big
{
	static bool bLastForceHost = false;
	void looped::system_spoofing()
	{
		if (bLastForceHost != g.session.force_session_host && gta_util::get_network()->m_game_session_state == 0)
		{
			std::uint64_t host_token;
			g_pointers->m_generate_uuid(&host_token);

			host_token = g.session.force_session_host ? (rand() % 10000) : host_token;

			*g_pointers->m_host_token = host_token;

			if (gta_util::get_network()->m_game_session_ptr)
				gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token = host_token;

			g_pointers->m_profile_gamer_info->m_host_token = host_token;
			g_pointers->m_player_info_gamer_info->m_host_token = host_token;
			(*g_pointers->m_communications)->m_voice.m_connections[0]->m_gamer_info.m_host_token = host_token;

			if (g_local_player && g_local_player->m_player_info)
				g_local_player->m_player_info->m_net_player_data.m_host_token = host_token;

			bLastForceHost = g.session.force_session_host;
		}

		if (g.spoofing.rockstar_id != g.spoofing.applied_spoof_rockstar_id && gta_util::get_network()->m_game_session_state == 0)
		{
			g.spoofing.applied_spoof_rockstar_id = g.spoofing.rockstar_id;
		}

		if (g.spoofing.spoof_rockstar_id != g.spoofing.should_spoof_rockstar_id && gta_util::get_network()->m_game_session_state == 0)
		{
			g.spoofing.should_spoof_rockstar_id = g.spoofing.spoof_rockstar_id;
		}
	}
}
