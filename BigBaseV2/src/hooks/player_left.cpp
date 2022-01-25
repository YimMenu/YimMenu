#include "hooking.hpp"

namespace big
{
	void hooks::player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		LOG(INFO) << "Player '" << net_player->get_name() << "' leaved freeing slot #" << (int)net_player->player_id;

		return g_hooking->m_player_has_left_hook.get_original<decltype(&hooks::player_leave)>()(_this, net_player);
	}
}