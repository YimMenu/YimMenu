#pragma once
#include "script_global.hpp"

namespace big::scr_globals
{
	namespace size
	{
		constexpr int globalplayer_bd = 453;
		constexpr int gpbd_fm_3 = 599;
		constexpr int gpbd_fm_1 = 888;
	}

	namespace offset
	{
		namespace globalplayer_bd
		{
			constexpr int orbital_cannon_bitset = 416;
		}
	}

	static inline script_global gsbd(2680265);
	static inline script_global gsbd_fm(1835502);
	static inline script_global gsbd_kicking(1883751);
	static inline script_global gsbd_fm_events(1920255);
	static inline script_global gsbd_block_c(2683918);

	static inline script_global globalplayer_bd(2689235);
	static inline script_global gpbd_fm_3(1892703);
	static inline script_global gpbd_fm_1(1853348);

	static inline script_global launcher_global(2779753);

	static inline script_global sp(113386);
	static inline script_global mission_definition(91229);

	static inline script_global creator_job_metadata(4718592);
	static inline script_global terminate_creator(1574607); // NETWORK::NETWORK_BAIL(1, 0, 0); fm_*_creator
	static inline script_global switch_struct(1574632);
	static inline script_global mission_creator_radar_follows_camera(2621443);
	static inline script_global mission_creator_exited(1574530);

	static inline script_global in_multiplayer(78319); // g_bInMultiplayer

	static inline script_global vehicle_global = script_global(1585857);
	static inline script_global mechanic_global = script_global(2815059);

	static inline script_global spawn_global = script_global(2725439);
}

namespace big::scr_locals
{
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx = 597;
	}
}