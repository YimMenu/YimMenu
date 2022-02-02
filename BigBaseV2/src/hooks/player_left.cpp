#include "hooking.hpp"
#include "services/player_service.hpp"

namespace big
{
	void hooks::player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		g_player_service->player_leave(net_player);

		return g_hooking->m_player_has_left_hook.get_original<decltype(&hooks::player_leave)>()(_this, net_player);
	}
}