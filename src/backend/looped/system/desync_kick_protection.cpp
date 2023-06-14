#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "services/players/player_service.hpp"

#include <network/Network.hpp>

namespace big
{
	void looped::system_desync_kick_protection()
	{
		memset(&gta_util::get_network()->m_game_complaint_mgr.m_host_tokens_complained, 0, 64 * sizeof(std::uint64_t));

		if (!g_player_service->m_player_to_use_complaint_kick
		    || !g_player_service->m_player_to_use_complaint_kick->get()->get_net_data())
			gta_util::get_network()->m_game_complaint_mgr.m_num_tokens_complained = 0;
		else
		{
			gta_util::get_network()->m_game_complaint_mgr.m_num_tokens_complained = 1;
			gta_util::get_network()->m_game_complaint_mgr.m_host_tokens_complained[0] =
			    g_player_service->m_player_to_use_complaint_kick->get()->get_net_data()->m_host_token;
		}

		auto old = gta_util::get_network()->m_game_complaint_mgr.m_host_token;

		if (gta_util::get_network()->m_game_session_state > 3 && gta_util::get_network()->m_game_session_state < 6
		    && g_player_service->m_player_to_use_complaint_kick && g_player_service->get_self()->is_valid()
		    && !g_player_service->get_self()->is_host())
		{
			g_pointers->m_gta.m_reset_network_complaints(&gta_util::get_network()->m_game_complaint_mgr);
		}
	}
}