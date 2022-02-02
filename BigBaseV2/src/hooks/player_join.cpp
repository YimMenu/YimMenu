#include "hooking.hpp"
#include "services/player_service.hpp"

namespace big
{
	void hooks::player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		g_player_service->player_join(net_player);

		return g_hooking->m_player_has_joined_hook.get_original<decltype(&hooks::player_join)>()(_this, net_player);
	}
}