#include "hooking.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	void hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, std::uint64_t a2, std::uint32_t a3, std::uint32_t a4[4])
	{
		if (g.notifications.network_player_mgr_init.log)
			LOG(INFO) << "CNetworkPlayerMgr#init got called, we're probably entering a session.";
		if (g.notifications.network_player_mgr_init.notify)
			g_notification_service->push("NETWORK_PLAYER_MGR"_T.data(), "NETWORK_PLAYER_MGR_INIT"_T.data());

		g_hooking->get_original<hooks::network_player_mgr_init>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g.m_spoofed_peer_ids.clear();
		g_player_service->do_cleanup();

		if (g.notifications.network_player_mgr_shutdown.log)
			LOG(INFO) << "CNetworkPlayerMgr#shutdown got called, we're probably leaving our session.";
		if (g.notifications.network_player_mgr_shutdown.notify)
			g_notification_service->push("NETWORK_PLAYER_MGR"_T.data(), "NETWORK_PLAYER_MGR_DESTROY"_T.data());

		g_hooking->get_original<hooks::network_player_mgr_shutdown>()(_this);
	}
}
