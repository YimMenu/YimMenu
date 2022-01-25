#include "hooking.hpp"

namespace big
{
	void hooks::player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		LOG(INFO) << "Player '" << net_player->get_name() << "' joined taking slot #" << (int)net_player->player_id;

		return g_hooking->m_player_has_joined_hook.get_original<decltype(&hooks::player_join)>()(_this, net_player);
	}
}