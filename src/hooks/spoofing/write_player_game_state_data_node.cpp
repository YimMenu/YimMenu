#include "hooking.hpp"

namespace big
{
	bool hooks::write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node)
	{
		auto ret = g_hooking->get_original<write_player_game_state_data_node>()(player, node);

		if (g->spoofing.spoof_hide_god)
		{
			node->m_is_invincible = false;
			node->m_bullet_proof = false;
			node->m_collision_proof = false;
			node->m_explosion_proof = false;
			node->m_fire_proof = false;
			node->m_melee_proof = false;
			node->m_steam_proof = false;
			node->m_water_proof = false;
		}

		if (g->spoofing.spoof_hide_spectate)
		{
			node->m_is_spectating = false;
			node->m_spectating_net_id = 0;
		}

		return ret;
	}
}
