#pragma once
#include "script_global.hpp"
#include "script_local.hpp"

namespace big::scr_globals
{
	static inline const script_global gsbd(2648938);
	static inline const script_global gsbd_fm(1845281);
	static inline const script_global gsbd_kicking(1877042);
	static inline const script_global gsbd_fm_events(1916617);
	static inline const script_global gsbd_block_c(2652592);
	static inline const script_global gsbd_property_instances(1936863);

	static inline const script_global globalplayer_bd(2657971);
	static inline const script_global gpbd_fm_3(1887305);
	static inline const script_global gpbd_fm_1(1845281);
	static inline const script_global interiors(1943520);

	static inline const script_global launcher_global(2699171);

	static inline const script_global sp(114370); // check flow_controller
	static inline const script_global mission_definition(92160); // standard_global_init (66, "agency_heist1", "AH1", 230, 1, 1, -1, -1, 8192)

	// creator globals usually remain the same after updates
	static inline const script_global creator_job_metadata(4718592);
	static inline const script_global terminate_creator(1574607); // NETWORK::NETWORK_BAIL(1, 0, 0); fm_*_creator
	static inline const script_global switch_struct(1574633);
	static inline const script_global mission_creator_radar_follows_camera(2621443);
	static inline const script_global mission_creator_exited(1574530);

	static inline const script_global in_multiplayer(79389); // g_bInMultiplayer
	static inline const script_global transition_state(1575011);
	static inline const script_global sctv_spectator(2697731); // pausemenu_multiplayer function 0xE49C42EC

	static inline const script_global vehicle_global(1586521);

	static inline const script_global freemode_properties(2672855);
	static inline const script_global freemode_global(2738934);
	
	static inline const script_global spawn_global(2696212);
	
	static inline const script_global dance_state(1943520);

	static inline const script_global transaction_overlimit(20913);

	static inline const script_global stats(2359296);

	static inline const script_global session(1574589);
	static inline const script_global session2(1575035);
	static inline const script_global session3(32949);
	static inline const script_global session4(1574942);
	static inline const script_global session5(1575010);
	static inline const script_global session6(2696130); // freemode -> if (NETWORK::NETWORK_IS_GAME_IN_PROGRESS() && !NETWORK::NETWORK_IS_ACTIVITY_SESSION())

	static inline const script_global interaction_menu_access(2710429); // am_pi_menu -> if (NETWORK::NETWORK_IS_SIGNED_ONLINE()) first global after that

	static inline const script_global disable_wasted_sound(2707679); // freemode -> AUDIO::PLAY_SOUND_FRONTEND(-1, "Wasted", "POWER_PLAY_General_Soundset", true);
	
	static inline const script_global passive(1574582); // if (((!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(bVar1), false) || Global_

	static inline const script_global property_garage(1937684);
	static inline const script_global property_names(1312298);

	static inline const script_global reset_clothing(104077); // freemode 75, &iLocal_.*, 2\);


	static inline const script_global gun_van(1949748); // return -29.532f, 6435.136f, 31.162f;
}

namespace big::scr_locals
{
	namespace am_hunt_the_beast
	{
		constexpr static auto broadcast_idx        = 604;  // (bParam0) != 0;
		constexpr static auto player_broadcast_idx = 2588; // if (NETWORK::PARTICIPANT_ID_TO_INT() != -1)
	}

	namespace am_criminal_damage
	{
		constexpr static auto broadcast_idx = 115; // /* Tunable: CRIMINAL_DAMAGE_DISABLE_SHARE_CASH */)
		constexpr static auto score_idx     = 110; // AUDIO::PLAY_SOUND_FRONTEND(-1, "Criminal_Damage_High_Value", "GTAO_FM_Events_Soundset", false);
	}

	namespace am_cp_collection
	{
		constexpr static auto broadcast_idx        = 820; // bVar1 = NETWORK::NETWORK_GET_PLAYER_INDEX(PLAYER::INT_TO_PARTICIPANTINDEX(iVar0));
		constexpr static auto player_broadcast_idx = 3461; // bVar1 = NETWORK::NETWORK_GET_PLAYER_INDEX(PLAYER::INT_TO_PARTICIPANTINDEX(iVar0));
	}

	namespace am_king_of_the_castle
	{
		constexpr static auto broadcast_idx = 98; // KING_OF_THE_CASTLE_EVENT_TIME_LIMIT
	}

	namespace fmmc_launcher
	{
		constexpr static auto broadcast_idx = 12564; // if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(PLAYER::INT_TO_PLAYERINDEX(Global_
	}

	namespace fm_mission_controller
	{
		constexpr static auto mission_controller_wanted_state_flags = 60096; // if (PLAYER::GET_PLAYER_WANTED_LEVEL(bLocal_
	}

	namespace freemode
	{
		// first uLocal_ in this function call
		// func_\d+\((&.Local_\d+(, )?){9}\);
		inline static script_local mobile(19139);
	}

	namespace carmod_shop
	{
		inline static script_local maintainer(735); //P"4F ? ? 47 ? ? 73 58 ? ? 4F ? ? 25 ?" +1 W="maintainer" +3 W ="state"
		inline static auto state = 446;
		inline static script_local input_button(1867);  //P"51 ? ? 70 51 ? ? 50 ? ? 51 ? ?" +1 W="input_button"
		inline static script_local enabled_state(2097); //P"51 ? ? 71 51 ? ? 71 51 ? ? 71 61 ? ? ?" +1 W="enabled_state"
		inline static script_local ready(2048);         //P"51 ? ? 50 ? ? 2A" +1 W="ready"
		inline static auto vehicle_state  = 638;        //P"4F ? ? 46 ? ? 4F ? ?" +4 W ="vehicle_state"
		inline static auto vehicle_ent_id = 409;        //P"4F ? ? 47 ? ? 39 ? 55 ? ? 38 ? 73" +4 W ="vehicle_ent_id"
	}
}
