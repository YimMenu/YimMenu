#pragma once
#include "script_global.hpp"

namespace big::scr_globals
{
	static inline script_global gsbd(2648711);
	static inline script_global gsbd_fm(1835504);
	static inline script_global gsbd_kicking(1885447);
	static inline script_global gsbd_fm_events(1924276);
	static inline script_global gsbd_block_c(2652364);
	static inline script_global gsbd_property_instances(1944302);

	static inline script_global globalplayer_bd(2657704);
	static inline script_global gpbd_fm_3(1895156);
	static inline script_global gpbd_fm_1(1853988);

	static inline script_global launcher_global(2756336);

	static inline script_global sp(113810); // check flow_controller
	static inline script_global mission_definition(91601); // standard_global_init (66, "agency_heist1", "AH1", 230, 1, 1, -1, -1, 8192)

	// creator globals usually remain the same after updates
	static inline script_global creator_job_metadata(4718592);
	static inline script_global terminate_creator(1574607); // NETWORK::NETWORK_BAIL(1, 0, 0); fm_*_creator
	static inline script_global switch_struct(1574632);
	static inline script_global mission_creator_radar_follows_camera(2621443);
	static inline script_global mission_creator_exited(1574530);

	static inline script_global in_multiplayer(78689); // g_bInMultiplayer
	static inline script_global transition_state(1574996);

	static inline script_global vehicle_global  = script_global(1586488);
	static inline script_global mechanic_global = script_global(2794162);

	static inline script_global spawn_global = script_global(2694613);

	static inline script_global offradar_time(2672524);
}

namespace big::scr_locals
{
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx        = 600;
		constexpr static auto player_broadcast_idx = 2584;
	}

	namespace am_criminal_damage
	{
		constexpr static auto broadcast_idx = 111;
		constexpr static auto score_idx     = 106;
	}

	namespace am_cp_collection
	{
		constexpr static auto broadcast_idx        = 816;
		constexpr static auto player_broadcast_idx = 3457;
	}

	namespace am_king_of_the_castle
	{
		constexpr static auto broadcast_idx = 94;
	}

	namespace fmmc_launcher
	{
		constexpr static auto broadcast_idx = 11629;
	}
}