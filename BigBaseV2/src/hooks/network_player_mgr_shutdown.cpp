#include "hooking.hpp"
#include "services/player_service.hpp"

namespace big
{
	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g_player_service->do_cleanup();

		if (g->notifications.network_player_mgr_shutdown.log)
			LOG(INFO) << "CNetworkPlayerMgr#shutdown got called, we're probably leaving our session.";
		if (g->notifications.network_player_mgr_shutdown.notify)
			g_notification_service->push("Network Player Manager", "Leaving session and cleaning up player data.");

		return g_hooking->m_network_player_mgr_shutdown_hook.get_original<decltype(&hooks::network_player_mgr_shutdown)>()(_this);
	}
}