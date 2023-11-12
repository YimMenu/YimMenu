#include "core/data/network.hpp"
#include "hooking.hpp"
#include "services/players/player_service.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	bool hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4])
	{
		bool result = g_hooking->get_original<hooks::network_player_mgr_init>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);
		g_network.network_player_mgr_init = true;

		return result;
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g_player_service->do_cleanup();
		self::spawned_vehicles.clear();
		g_network.network_player_mgr_init      = false;
		g_network.auto_kick_host_when_attacked = false;

		g_hooking->get_original<hooks::network_player_mgr_shutdown>()(_this);
	}
}
