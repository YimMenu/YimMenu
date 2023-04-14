#pragma once
#include "pointers.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

#include <script/scrProgramTable.hpp>

namespace big
{
	void register_script_patches()
	{
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("freemode"), "2D 01 08 00 ? 38 00 5D ? ? ? 2A 06", 5, {0x71, 0x2E, 0x01, 0x01}, &g.session.decloak_players});
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"), "2D 01 04 00 ? 2C ? ? ? 5D ? ? ? 71 57 ? ? 2C", 5, {0x2E, 0x01, 0x00}, nullptr});// script host kick
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("freemode"), "2D 00 03 00 00 5D ? ? ? 71 08", 5, {0x2E, 0x00, 0x00}, &g.tunables.no_idle_kick});
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"),
		    "2D 00 03 00 00 5D ? ? ? 56 ? ? 72 2E ? ? 62",
		    5,
		    {0x72, 0x2E, 0x00, 0x01},
		    &g.tunables.no_idle_kick});
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"), "5D ? ? ? 76 57 ? ? 5D ? ? ? 76", 0, {0x2E, 0x00, 0x00}, nullptr});// end session kick protection
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"), "2D 01 09 00 00 5D ? ? ? 56 ? ? 2E", 5, {0x2E, 0x01, 0x00}, nullptr});// disable death when undermap/spectating
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"), "71 2E ? ? 55 ? ? 61 ? ? ? 47 ? ? 63", 0, {0x72}, nullptr});// load island even if stranded animal IPL choice is not set
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"), "2D 00 07 00 00 7B", 5, {0x2E, 0x00, 0x00}, nullptr});// disable population load balancing
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("freemode"), "2D 02 08 00 00 38 01 56", 5, {0x2E, 0x02, 0x00}, &g.session.block_muggers});
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"), "2D 00 CF 00 00", 5, {0x2E, 0x00, 0x00}, &g.session.block_ceo_raids});
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("freemode"), "06 56 ? ? 38 02 2C ? ? ? 71 71", 0, {0x2B, 0x55}, &g.spoofing.spoof_blip});// prevent normal blip update
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("freemode"), "2C ? ? ? 55 ? ? 71 2C ? ? ? 61", 7, std::vector<uint8_t>(16, 0x0), &g.spoofing.spoof_blip});// prevent normal blip update 2
		g_script_patcher_service->add_patch({RAGE_JOAAT("shop_controller"), "2D 01 04 00 00 2C ? ? ? 56 ? ? 71", 5, {0x71, 0x2E, 0x01, 0x01}, nullptr});// despawn bypass
		g_script_patcher_service->add_patch({RAGE_JOAAT("shop_controller"), "38 00 5D ? ? ? 38 00 5D ? ? ? 38 00 41", 0, std::vector<uint8_t>(12, 0x0), nullptr});// godmode/invisibility detection bypass
		g_script_patcher_service->add_patch({RAGE_JOAAT("am_mp_nightclub"),
		    "2D 01 03 00 00 2C ? ? ? 56 ? ? 72 2E ? ? 38 00",
		    5,
		    {0x72, 0x2E, 0x01, 0x01},
		    &g.self.dance_mode});
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("am_mp_nightclub"), "20 56 ? ? 4F ? ? 46 ? ? 41 ? 71", 0, {0x2B, 0x55}, &g.self.dance_mode});
		g_script_patcher_service->add_patch({RAGE_JOAAT("freemode"),
		    "5D ? ? ? 56 ? ? 72 39 05 38 04 2C ? ? ? 58",
		    0,
		    {0x2B, 0x2B, 0x2B, 0x00, 0x55},
		    &g.self.invisibility});

		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("carmod_shop"), "2D 01 0A 00 00 4F ? ? 40 ? 41 ? 39 03", 5, {0x2E, 0x01, 0x00}, &g.vehicle.ls_customs});// disable camera
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("carmod_shop"), "2D 02 10 00 00 2C", 5, {0x71, 0x2E, 0x02, 0x01}, &g.vehicle.ls_customs});
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("carmod_shop"), "2D 00 B8 00 00", 5, {0x2E, 0x00, 0x00}, &g.vehicle.ls_customs});
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("carmod_shop"), "06 1F 56 ? ? 62 ? ? ? 56", 0, {0x2B, 0x2B, 0x55}, &g.vehicle.ls_customs});// buy mods for free in SP
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("carmod_shop"), "2D 03 16 00 00 5D", 5, {0x72, 0x2E, 0x03, 0x01}, &g.vehicle.ls_customs});// allow all vehicles
		g_script_patcher_service->add_patch(
		    {RAGE_JOAAT("carmod_shop"), "2D 03 07 00 00 71 38 02", 5, {0x72, 0x2E, 0x03, 0x01}, &g.vehicle.ls_customs});// allow all vehicles 2

		for (auto& entry : *g_pointers->m_script_program_table)
		{
			if (entry.m_program)
				g_script_patcher_service->on_script_load(entry.m_program);
		}
	}
}