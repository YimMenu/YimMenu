#include "hooking/hooking.hpp"
#include "util/model_info.hpp"

#include <netsync/nodes/physical/CPhysicalScriptGameStateDataNode.hpp>

namespace big
{
	void hooks::write_physical_script_game_state_data_node(__int64 iface, CPhysicalScriptGameStateDataNode* node)
	{
		g_hooking->get_original<hooks::write_physical_script_game_state_data_node>()(iface, node);

		auto entity = reinterpret_cast<CVehicle*>((((rage::netObject*)(iface - 0x130)))->GetGameObject());

		if (g.spoofing.spoof_hide_veh_god && g_local_player && self::veh)
		{
			if (g_local_player->m_vehicle && g_local_player->m_vehicle == entity)
			{
				node->m_godmode = false;
				node->m_bullet_proof = false;
				node->m_fire_proof   = false;
				node->m_smoke_proof  = false;
				node->m_steam_proof  = false;
				node->m_collision_proof = false;
				node->m_explosion_proof = false;
				node->m_melee_proof     = false;
			}
		}
	}
}
