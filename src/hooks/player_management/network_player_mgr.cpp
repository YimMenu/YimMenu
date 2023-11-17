#include "core/data/network.hpp"
#include "core/data/vehicle.hpp"
#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include "services/vehicle_preview/vehicle_preview.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	bool hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4])
	{
		LOG(INFO) << "CNetworkPlayerMgr#init got called, we're probably entering a session.";

		bool result = g_hooking->get_original<hooks::network_player_mgr_init>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);

		return result;
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		LOG(INFO) << "CNetworkPlayerMgr#shutdown got called, we're probably leaving our session.";

		g_player_service->do_cleanup();
		self::spawned_vehicles.clear();
		g_network.auto_kick_host_when_attacked = false;

		if (g_vehicle.preview_vehicle)
		{
			g_vehicle.preview_vehicle = false;
			g_vehicle_preview.reset();
		}

		g_hooking->get_original<hooks::network_player_mgr_shutdown>()(_this);
	}
}
