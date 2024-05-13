#include "hooking/hooking.hpp"
#include "util/model_info.hpp"

#include <netsync/nodes/physical/CPhysicalScriptGameStateDataNode.hpp>

namespace big
{
	void hooks::write_physical_script_game_state_data_node(rage::CPhysical* this_ptr, CPhysicalScriptGameStateDataNode* node)
	{
		g_hooking->get_original<hooks::write_physical_script_game_state_data_node>()(this_ptr, node);

		auto this_vehicle = (*(CVehicle*(__fastcall**)(char*))(*((DWORD64*)this_ptr - 38) + 0xC0))((char*)this_ptr - 304);

		if (g.spoofing.spoof_hide_veh_god && g_local_player && self::veh)
		{
			if (g_local_player->m_vehicle && g_local_player->m_vehicle == this_vehicle)
			{
				node->m_godmode         = false;
				node->m_bullet_proof    = false;
				node->m_fire_proof      = false;
				node->m_smoke_proof     = false;
				node->m_steam_proof     = false;
				node->m_collision_proof = false;
				node->m_explosion_proof = false;
				node->m_melee_proof     = false;
			}
		}
	}
}
