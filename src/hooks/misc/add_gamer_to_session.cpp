#include "gta_util.hpp"
#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"

#include <network/CNetGamePlayerDataMsg.hpp>
#include <network/Network.hpp>
#include <network/RemoteGamerInfoMsg.hpp>

namespace big
{
	bool hooks::add_gamer_to_session(rage::netConnectionManager* mgr, std::uint32_t msg_id, int* req_id, RemoteGamerInfoMsg* info, int flags, void* a6)
	{
		if (g.session.hide_token_spoofing_when_host
		    && info->m_gamer_info.m_gamer_handle.m_rockstar_id == g_player_service->get_self()->get_rockstar_id())
		{
			info->m_gamer_info.m_host_token = g.session.original_host_token;
			info->m_gamer_info.m_peer_id = (info->m_gamer_info.m_peer_id & 0xFFFFFFFF) | (g.session.original_host_token << 32); // TODO: P2pSecurity info message
		}

		return g_hooking->get_original<hooks::add_gamer_to_session>()(mgr, msg_id, req_id, info, flags, a6);
	}
}