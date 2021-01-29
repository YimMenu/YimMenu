#include "hooking.hpp"

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::netPlayerData* local_player, int64_t a2, int64_t a3, DWORD* a4)
	{
		const char name[20] = "How dare you!";
		memcpy(local_player->m_name, name, sizeof(name));

		return g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
	}
}