#include "hooking.hpp"
#include <datanodes/player/CPlayerGameStateDataNode.hpp>
#include "natives.hpp"

namespace big
{
	bool is_player_in_cutscene(Player player) { return NETWORK::NETWORK_IS_PLAYER_IN_MP_CUTSCENE(player); }

	bool is_player_in_interior(Ped player) { return (INTERIOR::GET_INTERIOR_FROM_ENTITY(player) != 0); }

	bool hooks::write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node)
	{
		auto ret = g_hooking->get_original<write_player_game_state_data_node>()(player, node);

		if (g.spoofing.spoof_hide_god && !is_player_in_cutscene(self::id) && !is_player_in_interior(self::ped))
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

		if (g.spoofing.spoof_hide_spectate)
		{
			node->m_is_spectating = false;
			node->m_spectating_net_id = 0;
		}

		return ret;
	}
}
