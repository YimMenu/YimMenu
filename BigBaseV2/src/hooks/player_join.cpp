#include "hooking.hpp"
#include "services/player_service.hpp"

namespace big
{
	void hooks::player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		LOG(INFO) << "Player '" << net_player->get_name() << "' joined taking slot #" << (int)net_player->m_player_id;

		g_player_service->player_join(net_player);

		return g_hooking->m_player_has_joined_hook.get_original<decltype(&hooks::player_join)>()(_this, net_player);
	}
}