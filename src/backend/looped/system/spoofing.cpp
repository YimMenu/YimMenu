#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
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
		if (bLastForceHost != g.session.force_session_host && gta_util::get_network()->m_game_session_state == 0)
		{
			std::uint64_t host_token;
			g_pointers->m_generate_uuid(&host_token);

			host_token = g.session.force_session_host ? (rand() % 10000) : host_token;

			*g_pointers->m_host_token = host_token;

			if (gta_util::get_network()->m_game_session_ptr)
				gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token = host_token;

			g_pointers->m_profile_gamer_info->m_host_token                                       = host_token;
			g_pointers->m_player_info_gamer_info->m_host_token                                   = host_token;
			(*g_pointers->m_communications)->m_voice.m_connections[0]->m_gamer_info.m_host_token = host_token;

			if (g_local_player && g_local_player->m_player_info)
				g_local_player->m_player_info->m_net_player_data.m_host_token = host_token;

			bLastForceHost = g.session.force_session_host;
		}

		if (*g_pointers->m_is_session_started)
		{
			gta_util::execute_as_script(RAGE_JOAAT("freemode"), [] {
				if (NETWORK::NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() && NETWORK::NETWORK_GET_SCRIPT_STATUS() == 2)
				{
					if (g.spoofing.spoof_rank)
						scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].PlayerStats.Rank = g.spoofing.rank;

					if (g.spoofing.spoof_job_points)
						scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].JobPoints = g.spoofing.job_points;

					if (g.spoofing.spoof_kd_ratio)
						scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].PlayerStats.KdRatio = g.spoofing.kd_ratio;

					if (g.spoofing.spoof_blip)
					{
						if (g.spoofing.blip_type == 0)// random
							scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].PlayerBlip.PlayerVehicleBlipType = (eBlipType)(rand() % 90);
						else
							scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].PlayerBlip.PlayerVehicleBlipType =
							    (eBlipType)(g.spoofing.blip_type - 1);
					}
				}
			});
		}
	}
}
