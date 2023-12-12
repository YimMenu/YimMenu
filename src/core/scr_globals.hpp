#pragma once
#include "script_global.hpp"
#include "script_local.hpp"

namespace big::scr_globals
{
	static inline const script_global gsbd(2648918);
	static inline const script_global gsbd_fm(1845263);
	static inline const script_global gsbd_kicking(1877042);
	static inline const script_global gsbd_fm_events(1916087);
	static inline const script_global gsbd_block_c(2652572);
	static inline const script_global gsbd_property_instances(1936138);

	static inline const script_global globalplayer_bd(2657921);
	static inline const script_global gpbd_fm_3(1886967);
	static inline const script_global gpbd_fm_1(1845263);
	static inline const script_global interiors(1942781);

	static inline const script_global launcher_global(2698947);

	static inline const script_global sp(114370); // check flow_controller
	static inline const script_global mission_definition(92160); // standard_global_init (66, "agency_heist1", "AH1", 230, 1, 1, -1, -1, 8192)

	// creator globals usually remain the same after updates
	static inline const script_global creator_job_metadata(4718592);
	static inline const script_global terminate_creator(1574607); // NETWORK::NETWORK_BAIL(1, 0, 0); fm_*_creator
	static inline const script_global switch_struct(1574632);
	static inline const script_global mission_creator_radar_follows_camera(2621443);
	static inline const script_global mission_creator_exited(1574530);

	static inline const script_global in_multiplayer(79248); // g_bInMultiplayer
	static inline const script_global transition_state(1575008);
	static inline const script_global sctv_spectator(2697509); // pausemenu_multiplayer function 0xE49C42EC

	static inline const script_global vehicle_global(1586504);

	static inline const script_global freemode_properties(2672741);
	static inline const script_global freemode_global(2738587);

	static inline const script_global spawn_global(2695991);

	static inline const script_global dance_state(1942774);

	static inline const script_global transaction_overlimit(20796);

	static inline const script_global stats(2359296);

	static inline const script_global session(1574589);
	static inline const script_global session2(1575032);
	static inline const script_global session3(32829);
	static inline const script_global session4(1574941);
	static inline const script_global session5(1575007);
	static inline const script_global session6(2695909);

	static inline const script_global gooch(1882037);

	static inline const script_global gun_van(1948900);

	static inline const script_global interaction_menu_access(2710115); // am_pi_menu -> PI_BIK_13_2_H -> global = true;

	static inline const script_global disable_wasted_sound(2707352); // freemode -> AUDIO::PLAY_SOUND_FRONTEND(-1, "Wasted", "POWER_PLAY_General_Soundset", true);

	static inline const script_global passive(1574582);

	static inline const script_global property_garage(1936959);
	static inline const script_global property_names(1312263);

	static inline const script_global pickups(2707706);

	static inline const script_global reset_clothing(103936); // freemode 75, &iLocal_.*, 2\);
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

	namespace fm_mobile
	{
		// first uLocal_ in this function call
		// func_\d+\((&.Local_\d+(, )?){9}\);
		inline static script_local mobile(18717);
	}
}