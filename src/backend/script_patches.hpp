#pragma once
#include "services/script_patcher/script_patcher_service.hpp"
#include <script/scrProgramTable.hpp>

namespace big
{
	void register_script_patches()
	{
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 08 00 ? 38 00 5D ? ? ? 2A 06", 5, {0x6E, 0x2E, 0x01, 0x01}, &g->session.decloak_players });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 04 00 ? 2C ? ? ? 5D ? ? ? 6E 57 ? ? 2C", 5, { 0x2E, 0x01, 0x00 }, &g->protections.script_host_kick });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 08 00 00 5D ? ? ? 56 ? ? 6E", 5, { 0x2E, 0x01, 0x00 }, &g->tunables.no_idle_kick });
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "5D ? ? ? 73 57 ? ? 5D ? ? ? 73", 0, { 0x2E, 0x00, 0x00 }, nullptr }); // end session kick protection
		g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 09 00 00 5D ? ? ? 56 ? ? 2E", 5, { 0x2E, 0x01, 0x00 }, nullptr }); // disable death when undermap/spectating
		g_script_patcher_service->add_patch({ RAGE_JOAAT("shop_controller"), "2D 01 04 00 00 2C ? ? ? 56 ? ? 6E", 5, { 0x6E, 0x2E, 0x01, 0x01 }, nullptr }); // despawn bypass
		g_script_patcher_service->add_patch({ RAGE_JOAAT("shop_controller"), "38 00 5D ? ? ? 38 00 5D ? ? ? 38 00 41", 0, std::vector<uint8_t>(12, 0x0), nullptr}); // godmode/invisibility detection bypass

		for (auto& entry : *g_pointers->m_script_program_table)
		{
			if (entry.m_program)
				g_script_patcher_service->on_script_load(entry.m_program);
		}
	}
}