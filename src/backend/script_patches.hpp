#pragma once
#include "services/script_patcher/script_patcher_service.hpp"
#include <script/scrProgramTable.hpp>

namespace big
{
	void register_script_patches()
	{
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 08 00 ? 38 00 5D ? ? ? 2A 06", 5, {0x71, 0x2E, 0x01, 0x01}, &g.session.decloak_players });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 04 00 ? 2C ? ? ? 5D ? ? ? 71 57 ? ? 2C", 5, { 0x2E, 0x01, 0x00 }, nullptr }); // script host kick
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 00 07 00 00 5D ? ? ? 56 ? ? 71", 5, { 0x2E, 0x00, 0x00 }, &g.tunables.no_idle_kick });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "5D ? ? ? 76 57 ? ? 5D ? ? ? 76", 0, { 0x2E, 0x00, 0x00 }, nullptr }); // end session kick protection
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 09 00 00 5D ? ? ? 56 ? ? 2E", 5, { 0x2E, 0x01, 0x00 }, nullptr }); // disable death when undermap/spectating
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "71 2E ? ? 55 ? ? 61 ? ? ? 47 ? ? 63", 0, { 0x72 }, nullptr });  // load island even if stranded animal IPL choice is not set
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 00 07 00 00 7B", 5, { 0x2E, 0x00, 0x00 }, nullptr });  // disable population load balancing
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 02 08 00 00 38 01 56", 5, { 0x2E, 0x02, 0x00 }, &g.session.block_muggers });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 00 CF 00 00 ", 5, { 0x2E, 0x00, 0x00 }, &g.session.block_ceo_raids });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("shop_controller"), "2D 01 04 00 00 2C ? ? ? 56 ? ? 71", 5, { 0x71, 0x2E, 0x01, 0x01 }, nullptr }); // despawn bypass
		g_script_patcher_service->add_patch({ RAGE_JOAAT("shop_controller"), "38 00 5D ? ? ? 38 00 5D ? ? ? 38 00 41", 0, std::vector<uint8_t>(12, 0x0), nullptr}); // godmode/invisibility detection bypass

		for (auto& entry : *g_pointers->m_script_program_table)
		{
			if (entry.m_program)
				g_script_patcher_service->on_script_load(entry.m_program);
		}
	}
}