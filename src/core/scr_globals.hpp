#pragma once
#include "script_global.hpp"

namespace big::scr_globals
{
	namespace size
	{
		constexpr int globalplayer_bd = 466;
		constexpr int gpbd_fm_3       = 608;
		constexpr int gpbd_fm_1       = 862;
	}

	static inline script_global gsbd(2648605);
	static inline script_global gsbd_fm(1835504);
	static inline script_global gsbd_kicking(1885209);
	static inline script_global gsbd_fm_events(1923597);
	static inline script_global gsbd_block_c(2652258);
	static inline script_global gsbd_property_instances(1943595);

	static inline script_global globalplayer_bd(2657589);
	static inline script_global gpbd_fm_3(1894573);
	static inline script_global gpbd_fm_1(1853910);

	static inline script_global launcher_global(2756259);

	static inline script_global sp(113648);
	static inline script_global mission_definition(91469);

	static inline script_global creator_job_metadata(4718592);
	static inline script_global terminate_creator(1574607);// NETWORK::NETWORK_BAIL(1, 0, 0); fm_*_creator
	static inline script_global switch_struct(1574632);
	static inline script_global mission_creator_radar_follows_camera(2621443);
	static inline script_global mission_creator_exited(1574530);

	static inline script_global in_multiplayer(78558);// g_bInMultiplayer
	static inline script_global transition_state(1574993);

	static inline script_global vehicle_global  = script_global(1586468);
	static inline script_global mechanic_global = script_global(2793046);

	static inline script_global spawn_global = script_global(2694562);
}

namespace big::scr_locals
{
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx        = 599;
		constexpr static auto player_broadcast_idx = 2583;
	}

	namespace am_criminal_damage
	{
		constexpr static auto broadcast_idx = 110;
		constexpr static auto score_idx     = 105;
	}

	namespace am_cp_collection
	{
		constexpr static auto broadcast_idx        = 815;
		constexpr static auto player_broadcast_idx = 3456;
	}

	namespace am_king_of_the_castle
	{
		constexpr static auto broadcast_idx = 93;
	}

	namespace fmmc_launcher
	{
		constexpr static auto broadcast_idx = 11153;
	}
}