#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"

#include <netsync/nodes/player/CPlayerGameStateDataNode.hpp>

namespace big
{
	static bool is_in_cutscene()
	{
		if (g_local_player && g_local_player->m_player_info)
			return g_local_player->m_player_info->m_game_state == eGameState::InMPCutscene;
		return false;
	}

	static bool is_in_interior()
	{
		int id = 0;
		if (auto self_ptr = g_player_service->get_self(); self_ptr->is_valid())
			id = self_ptr->id();
		return globals::get_interior_from_player(id) != 0;
	}

	bool hooks::write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node)
	{
		auto ret = g_hooking->get_original<write_player_game_state_data_node>()(player, node);

		if (g.spoofing.spoof_hide_god && !is_in_cutscene() && !is_in_interior())
		{
			node->m_is_invincible   = false;
			node->m_bullet_proof    = false;
			node->m_collision_proof = false;
			node->m_explosion_proof = false;
			node->m_fire_proof      = false;
			node->m_melee_proof     = false;
			node->m_steam_proof     = false;
			node->m_water_proof     = false;
		}

		if (g.spoofing.spoof_hide_spectate)
		{
			node->m_is_spectating     = false;
			node->m_spectating_net_id = 0;
		}

		return ret;
	}
}
