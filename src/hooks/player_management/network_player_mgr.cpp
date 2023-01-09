#include "hooking.hpp"
#include "memory/byte_patch.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	static memory::byte_patch* local_name_patch{};

	void hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, std::uint64_t a2, std::uint32_t a3, std::uint32_t a4[4])
	{
		if (g.notifications.network_player_mgr_init.log)
			LOG(INFO) << "CNetworkPlayerMgr#init got called, we're probably entering a session.";
		if (g.notifications.network_player_mgr_init.notify)
			g_notification_service->push("Network Player Manager", "Entering session and initializing player data.");

		// set our local spoofed name
		if (g.spoofing.spoof_username && g.spoofing.spoof_local_username)
		{
			std::array<char, 17> local_name;
			std::copy(g.spoofing.username.begin(), g.spoofing.username.end(), local_name.data());
			local_name_patch = memory::byte_patch::make(g_pointers->m_chat_gamer_info->m_name, local_name).get();
			local_name_patch->apply();
		}

		g_hooking->get_original<hooks::network_player_mgr_init>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g.m_spoofed_peer_ids.clear();
		g_player_service->do_cleanup();

		// restore our original name
		if (strcmp(g_pointers->m_chat_gamer_info->m_name, _this->m_local_net_player->get_name()) && local_name_patch)
		{
			local_name_patch->remove();
		}

		if (g.notifications.network_player_mgr_shutdown.log)
			LOG(INFO) << "CNetworkPlayerMgr#shutdown got called, we're probably leaving our session.";
		if (g.notifications.network_player_mgr_shutdown.notify)
			g_notification_service->push("Network Player Manager", "Leaving session and cleaning up player data.");

		g_hooking->get_original<hooks::network_player_mgr_shutdown>()(_this);
	}
}
