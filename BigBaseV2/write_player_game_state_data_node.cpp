#include "hooking.hpp"

namespace big
{
	bool hooks::write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node)
	{
		auto ret = g_hooking->m_write_player_game_state_data_node_hook.get_original<decltype(&write_player_game_state_data_node)>()(player, node);

		if (g->spoofing.spoof_hide_god)
			node->m_is_invincible = false;

		return ret;
	}
}
